--- SETUP FOR WINDOWS ---

# Download msys2
https://www.msys2.org/

# Launch the correct version
MSYS2 MINGW64

---- FIRST TIME CONFIG START ----

# Initial setup
pacman -Syu

# Important libraries, audio and video formats
pacman -S --needed base-devel mingw-w64-x86_64-toolchain nasm yasm pkg-config mingw-w64-x86_64-x264 mingw-w64-x86_64-fdk-aac mingw-w64-x86_64-lame mingw-w64-x86_64-x265 mingw-w64-x86_64-aom

---- FIRST TIME CONFIG END ----

- go to the folder where this txt file is at (example: cd /c/Users/greenlaser/Documents/_cpp/KalaVideo/_external_shared/ffmpeg)
- run 'bash build_all_any_platform.sh'

NOTE: It may take a minute to boot up the Shared builds so don't worry if its not reporting any info for a little while

--- SETUP FOR LINUX ---

simply run bash ./build_all_any_platform.sh