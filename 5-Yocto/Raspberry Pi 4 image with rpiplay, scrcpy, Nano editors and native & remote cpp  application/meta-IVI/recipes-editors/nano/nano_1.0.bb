# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# WARNING: the following LICENSE and LIC_FILES_CHKSUM values are best guesses - it is
# your responsibility to verify that the values are complete and correct.
#
# The following license files were not able to be identified and are
# represented as "Unknown" below, you will need to check them yourself:
#   COPYING.DOC
#
# NOTE: multiple licenses have been detected; they have been separated with &
# in the LICENSE value for now since it is a reasonable assumption that all
# of the licenses apply. If instead there is a choice between the multiple
# licenses then you should change the value to separate the licenses with |
# instead of &. If there is any doubt, check the accompanying documentation
# to determine which situation is applicable.
LICENSE = "GPL-3.0-only & Unknown"
LIC_FILES_CHKSUM = "file://COPYING;md5=f27defe1e96c2e1ecd4e0c9be8967949 \
                    file://COPYING.DOC;md5=ad1419ecc56e060eccf8184a87c4285f"


SRC_URI = "git://git.savannah.gnu.org/git/nano.git;protocol=https;branch=master;name=nano \
           git://git.savannah.gnu.org/git/gnulib.git;protocol=https;branch=master;name=gnulib;destsuffix=git/gnulib \ 
           file://0001-remove-cloning-gnulib-by-script-autogen.patch "


SRCREV_nano = "63a7be115a729190fdf612fd5b821ac015f2421e"
SRCREV_gnulib="4631e9b4d5d3bd5ba42864c7001cf3509a00c7b3"

SRCREV_FORMAT = "nano_gnulib"

# Modify these as desired
PV = "1.0+git${SRCPV}"


S = "${WORKDIR}/git"


DEPENDS = "zlib ncurses file"


inherit gettext pkgconfig autotools

EXTRA_OECONF = ""



do_autogen() {
   cd ${S}
   ./autogen.sh
}

addtask do_autogen before do_configure after do_unpack

do_configure(){
    oe_runconf
}

do_build(){

    oe_runmake
}

do_package_qa[noexec]="1"


