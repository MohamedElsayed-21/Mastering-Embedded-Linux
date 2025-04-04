# 1. Documentation variables 
SUMMARY = "Example for a simple recipe for c++ application"
DESCRIPTION = "This is a simple recipe for  remote  c++ application "
HOMEPAGE = " https://github.com/embeddedlinuxworkshop/y_t1"



# 2. lisence information
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""


# 3. soure code information

SRC_URI = "git://github.com/embeddedlinuxworkshop/y_t1;protocol=https;branch=master"

# github commit id
SRCREV = "49600e3cd69332f0e7b8103918446302457cd950"

#Package Version
PV = "1.0"


# source code download in ${WORKDIR}/git
S = "${WORKDIR}/git"


#  4. tasks  to be executed using bitbake
do_compile () {
	# Specify compilation commands here
	${CXX} ${S}/main.cpp -o cpp-app
}

do_install () {
	
	install -d ${D}${bindir}
	install -m 0755 cpp-app ${D}${bindir}
}

do_package_qa[noexec]="1"
