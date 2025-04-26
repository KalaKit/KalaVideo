#!/usr/bin/env bash
set -e

echo
echo "Building FFmpeg: Debug and Release"
echo "=========================================="
echo

# Check required tools
for tool in bash gcc make pkg-config nasm; do
  if ! command -v "$tool" &>/dev/null; then
    echo "[ERROR] $tool not found in PATH."
    exit 1
  else
    echo "[OK]    $tool"
  fi
done

echo
echo "===================="
echo

# Shared config
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
FFMPEG_DIR="$ROOT/ffmpeg"
CONFIGURE_SCRIPT="$FFMPEG_DIR/configure"

# Check for correct ffmpeg folder
if [ ! -d "$FFMPEG_DIR" ]; then
  echo "[ERROR] FFmpeg directory not found at: $FFMPEG_DIR"
  echo "Make sure the 'ffmpeg' source folder exists in this directory."
  exit 1
fi

# Check for configure script
if [ ! -f "$CONFIGURE_SCRIPT" ]; then
  echo "[ERROR] FFmpeg 'configure' script not found at: $CONFIGURE_SCRIPT"
  echo "Make sure the full FFmpeg source is present in the 'ffmpeg' folder."
  exit 1
fi

# Function to build FFmpeg with given options
build_ffmpeg() {
  local BUILD_TYPE=$1
  local CFLAGS=$2
  local DEBUG_FLAG=$3
  local INSTALL_DIR="$ROOT/install-$BUILD_TYPE"

  echo
  echo "==== Building $BUILD_TYPE ($INSTALL_DIR) ===="
  echo
  echo "FFMPEG TAKES A MINUTE TO BOOT UP, EVERYTHING IS WORKING AS INTENDED"
  echo

  rm -rf "$INSTALL_DIR"
  mkdir -p "$INSTALL_DIR"/{bin,lib,include}

  cd "$FFMPEG_DIR"

  ./configure \
	--prefix="$INSTALL_DIR" \
	--enable-shared \
	--disable-static \
	--disable-programs \
	--disable-doc \
	$DEBUG_FLAG \
	--extra-cflags="$CFLAGS" \
	--extra-ldflags="-Wl,--as-needed" \
	--disable-bzlib \
	--disable-iconv \
	--disable-vaapi \
	--disable-vdpau \
	--disable-hwaccels \
	--disable-network \
	--disable-schannel \
	--disable-sdl2 \
	--disable-securetransport \
	--enable-gpl \
	--enable-version3 \
	--enable-libx264 \
	--enable-libfdk-aac \
	--enable-libmp3lame \
	--enable-libx265 \
	--enable-libaom \
	--enable-nonfree
	
  make -j"$(nproc)" && make install || { echo "[ERROR] $BUILD_TYPE build failed"; exit 1; }

  echo
  echo "==== $BUILD_TYPE build complete! Installed to: $INSTALL_DIR ===="
  echo
}

# Build Debug
build_ffmpeg "debug" "-Og -g -pipe -march=native" "--enable-debug=3"

# Build Release
build_ffmpeg "release" "-O2 -pipe -march=native" "--disable-debug"

echo
echo "=========================================="
echo "All builds complete!"
echo
read -p "Press enter to exit…"
