SUMMARY = "Display and control your Android device."
HOMEPAGE = "https://github.com/Genymobile/scrcpy"


LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=968e58821ffcb172a8baa9bc799f0ad1"

SRC_URI = "git://github.com/Genymobile/scrcpy.git;protocol=https;branch=master;"

SRCREV = "baa10ed0a36ec775712be85f22d3db3f0a6e19f2"

S = "${WORKDIR}/git"

# libavcodec-dev libavdevice-dev libavformat-dev libavutil-dev  libswresample-dev
# wget gcc git 
# pkgconfig pkgconf meson ninja

DEPENDS = "ffmpeg libsdl2 meson-native ninja-native cmake-native pkgconfig-native libusb1"

RDEPENDS:${PN} += "android-tools ffmpeg libsdl2 libusb1 "


inherit meson pkgconfig gettext

INHERIT += "strip"

EXTRA_OEMESON += " \
  --buildtype=release \
  -Db_lto=true \
  -Dcompile_server=false \
  -Dprebuilt_server=${WORKDIR}/scrcpy-server-${PV} \
"


# do_package_qa[noexec]="1"


FILES:${PN} += "${datadir}/*"