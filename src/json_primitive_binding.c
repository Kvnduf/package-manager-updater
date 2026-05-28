#include "json_primitive_binding.h"
#include "utils.h"




int json_primitive_binding_init(json_primitive_binding_t* binding, char* json_field_name, json_primitive_type_t type, void* field_ptr, size_t field_size) {
    if (!binding || !json_field_name || !field_ptr || field_size == 0) return -1;
    
    binding->json_field_name = json_field_name;
    binding->type = type;
    binding->field_ptr = field_ptr;
    binding->field_size = field_size;
    return 0;
}

int json_primitive_binding_deserialize(const cJSON* json, json_primitive_binding_t* binding) {
    if (!json || !binding || !binding->json_field_name || !binding->field_ptr || binding->field_size == 0) return -1;
    
    cJSON* field = cJSON_GetObjectItemCaseSensitive(json, binding->json_field_name);
    if (!field) return 1;

    switch (binding->type)
    {
    case JSON_STRING:
        if (!cJSON_IsString(field)) return 1;
        if (secure_strncpy((char*)binding->field_ptr, field->valuestring, binding->field_size) != 0) return -1;
        break;
    case JSON_NUMBER:
        if (!cJSON_IsNumber(field)) return 1;
        if (binding->field_size == sizeof(int)) {
            *(int*)binding->field_ptr = field->valueint;
        } else if (binding->field_size == sizeof(double)) {
            *(double*)binding->field_ptr = field->valuedouble;
        } else {
            return -1;
        }
        break;
    case JSON_BOOL:
        if (!cJSON_IsBool(field)) return 1;
        *(cJSON_bool*)binding->field_ptr = cJSON_IsTrue(field) ? 1 : 0;
        break;
    case JSON_NULL:
        if (!cJSON_IsNull(field)) return 1;
        if (binding->field_size != sizeof(void*)) return -1;
        *(void**)binding->field_ptr = NULL;
        break;
    default:
        return -1;
    }
    return 0;
}
