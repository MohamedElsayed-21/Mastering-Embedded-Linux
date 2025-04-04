DOCUMENTATION = "appssl"
SUMMARY = "this appssl app is a simple example of a C++ application with dependencies" 



LICENSE = "CLOSED"

PV = "1.0"


SRC_URI = "file://appssl.cpp"

S = "${WORKDIR}"
DEPENDS = "openssl"

do_compile () {

	${CXX} ${LDFLAGS} ${S}/appssl.cpp  -lssl -lcrypto -o appssl
}

do_install () {
	
	install -d ${D}${bindir}
	install -m 0755 ${S}/appssl ${D}${bindir}
}

