# Package manager updater

A simple program to update package managers on Linux systems. It reads the list of package managers from a specific configuration file and for each package manager :

- **Executes the upgrade command**
- **Cleans orphaned packages**
- **Cleans the cache**

## Table of contents

- [Building the program](#building-the-program)
  - [Simple build](#simple-build)
  - [Build with wakelock support](#Build-with-wakelock-support)
    - [Build with Dbus wakelock support](#build-with-dbus-wakelock-support)
- [Setting up / Usage](#setting-up--usage)
  - [Configuration file](#configuration-file)
  - [Running the program](#running-the-program)
- [License](#license)

## Building the program

### Simple build

To have a simple generic build, you can execute the following command :

```bash
make
```

But you can also specify variables (GNU make) to customize the build process.

### Build with wakelock support

To prevent the system from sleeping during the update process, you can build the program with wakelock support.

Some Linux distributions have different way to handle screensaver.

Only **Dbus** are supported for now (most modern Linux distributions include D-Bus by default), but maybe in the future, other methods will be added.

#### Build with Dbus wakelock support

Verify that you have the **Dbus development libraries** installed on your system. Then, verify that :

- `pkg-config --libs dbus-1` returns the correct flags for linking against Dbus.
- `pkg-config --cflags dbus-1` returns the correct flags for compiling with Dbus.

If everything is correct, you can build the program with the variable `dbus_wakelock` set to `1` :

```bash
make dbus_wakelock=1
```

## Setting up / Usage

### Configuration file

First of all, you need to create a configuration file that lists the package managers you want to update. **The configuration file should be at `~/.config/package-manager-updater/pacmans.json `**

The configuration file should be a JSON file which contains an **array of package manager objects**.

**Package manager object schema :**

```json
{
  "name": "string", // The name of the package manager (e.g., "Apt", "Dnf", "Pacman")
  "nameCmd": "string", // The package manager name command (e.g., "apt", "dnf", "pacman")
  "upgradeCmd": "string", // The command to upgrade packages (enable flags for non-interactive mode if necessary)
  "cleanOrphansCmd": "string", // The command to clean orphaned packages (enable flags for non-interactive mode if necessary)
  "cleanCacheCmd": "string" // The command to clean the cache  (enable flags for non-interactive mode if necessary)
}
```

For example, a configuration file for **Apt** and **Pacman** could look like this :

```json
[
  {
    "name": "APT",
    "nameCmd": "apt",
    "upgradeCmd": "sudo apt update && sudo apt upgrade -y",
    "cleanOrphansCmd": "sudo apt autoremove -y",
    "cleanCacheCmd": "sudo apt autoclean -y && sudo apt clean"
  },
  {
    "name": "Pacman",
    "nameCmd": "pacman",
    "upgradeCmd": "sudo pacman -Syu --noconfirm",
    "cleanOrphansCmd": "sudo pacman -Rns $(pacman -Qtdq) --noconfirm",
    "cleanCacheCmd": "sudo pacman -Sc  --noconfirm"
  }
]
```

> **Note** : Make sure to exactly follow the schema because in case of an parsing error, the program don't show you where the error is in the configuration file.

### Running the program

Run `./bin/update` in the terminal to launch the update process. It can be run with the following options :

- `-l` or `--list` : Display the list of package managers defined in the configuration file **(useful during the first usage to verify if the configuration file is correctly parsed)**.
- `-p` or `--poweroff` : Shutdown the system 5 seconds after the update process is completed.
- `-h` or `--help` : Display the help message.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
Moreover, the project is also using [cJSON v1.7.19](https://github.com/DaveGamble/cJSON) project which is licensed under the MIT License. See the [cJSON LICENSE](licenses/cJSON/LICENSE) file for more details.
