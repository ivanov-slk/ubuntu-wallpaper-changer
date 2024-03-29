# ubuntu-wallpaper-changer

A simple wallpaper changer for Ubuntu that chooses a wallpaper based on configurable randomized policy.

## Build

Just run `mkdir ./build; bash ./.git-hooks/run_build.sh`.
This will compile the source code and run all tests. An executable will be created in `./build` directory.

Tested on Ubuntu 18.04, 20.04 and 22.04; `cmake`: 3.16.3 and 3.25.1; `make`: 4.2.1 and 4.3; `gcc`: 9.3.0, 10.3.0 and 12.1.0.

## Configure

A configuration file - `config.cfg` - must be created in the same directory as the executable. It is loaded on start, so any configuration changes made during runtime will be loaded the next time the application is started.
The file should look like this:

```
# Path to the wallpapers, subdirectories will be traversed.
path=path/to/wallpapers

# Seconds before change, integer.
seconds_before_change=30

# Allowed extensions, case sensitive.
file_allowed_extensions=.png,.jpg,.jpeg,.PNG,.JPG,.JPEG

# Directories that should be skipped, comma-separated.
directory_exclusions=Dir1,Dir2

# Relative frequency for choosing the listed directories.
directory_priorities = Nature:3,Abstract:2,Arts:10

# Seconds before change if wallpaper from the configured directory is selected.
directory_seconds = Nature:45,Abstract:20

# Scale options for the configured directories. Defaults to `zoom`.
directory_pic_options = Nature:scaled, Abstract:scaled

# Randomization policy. Choose from {uniform, weighted}.
policy=weighted
```

Some notes on the policies:

- `uniform` will choose a random file under `path` or its subdirectories; it uses cache, so new files (added in the directories during runtime) will be ignored.
- `weighted` will traverse the directories, where on each level it will randomly choose a directory, e.g.: if there are two directories under `main`: `dir1` and `dir2`, as the algorithm enters `main` it will select `dir1` with probability 1/3, `dir2` with probability 1/3 and `.` with probability 1/3. The last thing is useful if there are both files and subdirectories in the same directory (`main` in this case).
  - this can be overriden by configuring the `directory_priorities`. E.g., if `dir1` is prioritized with "3" (others default to 1), then `dir1` will be selected with probability 3/5, `dir2` with probability 1/5 and `.` with probability 1/5.
  - new files will be eligible for selection as soon as the next wallpaper change.

## Run

Having built the application and set the configuration, just execute the compiled file (preferably with nohup). The application will create a log file (`log.txt`), where the full path to each chosen wallpaper will be stored.

## TO-DO / Ideas

- Consider supporting both light and dark themes for GNOME. Currently the command is different and the application needs to be recompiled on theme change.
- Consider not using system calls for wallpaper switching.
