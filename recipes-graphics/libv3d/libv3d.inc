DESCRIPTION = "GLES/EGL files for ${MACHINE}"
SECTION = "libs"
PRIORITY = "required"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "http://source.mynonpublic.com/edision/edision-libv3d-${PV}.tar.xz"
SRC_URI[sha256sum] = "e46a322e19859c013f76f3e6f827d44fb9b74d01d6294348b3c41915ffa8e23d"

S = "${WORKDIR}/edision-libv3d-${PV}"

ARCH_DIR_aarch64 = "lib64"
ARCH_DIR_arm = "lib"

FILES_SOLIBSDEV = ""
FILES_${PN} += "${libdir}/lib*${SOLIBSDEV}"
INSANE_SKIP_${PN} += "already-stripped dev-so ldflags"

INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_SYSROOT_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT  = "1"

do_configure[noexec] = "1"

do_compile[noexec] = "1"

do_install() {
	install -m 0755 -d ${D}${libdir}
	oe_soinstall ${S}/${ARCH_DIR}/libv3dplatform.so.${PV} ${D}${libdir}
	oe_soinstall ${S}/${ARCH_DIR}/libv3ddriver.so.${PV} ${D}${libdir}
	ln -s libv3ddriver.so.${PV} ${D}${libdir}/libEGL.so
	ln -s libv3ddriver.so.${PV} ${D}${libdir}/libGLESv2.so
	install -m 0755 -d ${D}/${includedir}
	install -m 0644 ${S}/include/v3dplatform.h ${D}${includedir}
	for d in EGL GLES GLES2 GLES3 KHR; do
		install -m 0755 -d ${D}${includedir}/$d
		for f in ${S}/include/$d/*.h; do
			install -m 0644 $f ${D}${includedir}/$d
		done
	done
}

