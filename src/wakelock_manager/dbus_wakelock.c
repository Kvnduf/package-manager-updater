#include <dbus/dbus.h>
#include "wakelock_manager/wakelock.h"
#include "wakelock_manager/dbus_wakelock.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t g_cookie = 0;
static DBusConnection *g_conn = NULL;

static bool dbus_wakelock_is_supported(void)
{
    DBusError err;
    dbus_error_init(&err);

    DBusConnection *conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (!conn) {
        if (dbus_error_is_set(&err))
            dbus_error_free(&err);
        return false;
    }
    dbus_bool_t has_owner = dbus_bus_name_has_owner(
        conn,
        "org.freedesktop.ScreenSaver",
        &err);

    if (dbus_error_is_set(&err)) {
        dbus_error_free(&err);
        dbus_connection_unref(conn);
        return false;
    }

    dbus_connection_unref(conn);
    return has_owner ? true : false;
}

static int dbus_wakelock_acquire(void)
{
    DBusError err;
    DBusMessage *msg = NULL;
    DBusMessage *reply = NULL;

    dbus_error_init(&err);

    if (!g_conn) {
        g_conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
        if (!g_conn)
            return -1;
    }

    msg = dbus_message_new_method_call(
        "org.freedesktop.ScreenSaver",
        "/org/freedesktop/ScreenSaver",
        "org.freedesktop.ScreenSaver",
        "Inhibit");

    if (!msg)
        return -1;

    const char *app = "com.example.player";
    const char *reason = "Playback active";

    if (!dbus_message_append_args(
            msg,
            DBUS_TYPE_STRING, &app,
            DBUS_TYPE_STRING, &reason,
            DBUS_TYPE_INVALID))
    {
        dbus_message_unref(msg);
        return -1;
    }

    const int timeout_ms = 5000;
    reply = dbus_connection_send_with_reply_and_block(
        g_conn,
        msg,
        timeout_ms,
        &err);

    dbus_message_unref(msg);

    if (!reply) {
        if (dbus_error_is_set(&err))
            dbus_error_free(&err);
        return -1;
    }

    if (!dbus_message_get_args(
            reply,
            &err,
            DBUS_TYPE_UINT32, &g_cookie,
            DBUS_TYPE_INVALID))
    {
        if (dbus_error_is_set(&err))
            dbus_error_free(&err);
        dbus_message_unref(reply);
        return -1;
    }

    dbus_message_unref(reply);

    return 0;
}

static int dbus_wakelock_release(void)
{
    if (!g_conn || g_cookie == 0)
        return 0;

    DBusError err;
    DBusMessage *msg;
    DBusMessage *reply;

    dbus_error_init(&err);

    msg = dbus_message_new_method_call(
        "org.freedesktop.ScreenSaver",
        "/org/freedesktop/ScreenSaver",
        "org.freedesktop.ScreenSaver",
        "UnInhibit");

    if (!msg)
        return -1;

    if (!dbus_message_append_args(
            msg,
            DBUS_TYPE_UINT32, &g_cookie,
            DBUS_TYPE_INVALID))
    {
        dbus_message_unref(msg);
        return -1;
    }
    const int timeout_ms = 5000;

    reply = dbus_connection_send_with_reply_and_block(
        g_conn,
        msg,
        timeout_ms,
        &err);

    dbus_message_unref(msg);

    if (!reply) {
        if (dbus_error_is_set(&err))
            dbus_error_free(&err);
        return -1;
    }

    dbus_message_unref(reply);

    g_cookie = 0;
    dbus_connection_unref(g_conn);
    g_conn = NULL;

    return 0;
}


int dbus_wakelock_init(wakelock_t* w) {
    if (!w) return -1;
    snprintf(w->name, sizeof(w->name), "DBus Wakelock");
    w->is_supported = dbus_wakelock_is_supported;
    w->acquire = dbus_wakelock_acquire;
    w->release = dbus_wakelock_release;
    return 0;
}
