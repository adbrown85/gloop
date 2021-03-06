# Check for Autoconf
AC_PREREQ([2.67])

# Initialize package information
define([MY_NAME], [Gloop])
define([MY_MAJOR_VERSION], [0])
define([MY_MINOR_VERSION], [7])
define([MY_INCREMENTAL_VERSION], [2])
define([MY_VERSION], MY_MAJOR_VERSION.MY_MINOR_VERSION.MY_INCREMENTAL_VERSION)
define([MY_EMAIL], [adb1413@rit.edu])
define([MY_TARNAME], [gloop])
define([MY_URL], [http://github.com/adbrown85/gloop])
define([MY_DESCRIPTION], ['Lightweight C++ wrapper for OpenGL'])
AC_INIT(MY_NAME, MY_VERSION, MY_EMAIL, MY_TARNAME, MY_URL)
AC_CONFIG_SRCDIR([gloop/common.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_SUBST([PACKAGE_MAJOR_VERSION], MY_MAJOR_VERSION)
AC_SUBST([PACKAGE_MINOR_VERSION], MY_MINOR_VERSION)
AC_SUBST([PACKAGE_INCREMENTAL_VERSION], MY_INCREMENTAL_VERSION)
AC_SUBST([PACKAGE_DESCRIPTION], MY_DESCRIPTION)

# Check for system
AC_CANONICAL_HOST

# Check for compilers and languages
AC_PROG_CC
AC_PROG_CXX
AC_LANG([C++])
if test "$host_vendor" = 'apple'; then
    AC_PROG_OBJCXX
fi

# Check for common headers
AC_HEADER_STDBOOL

# Check for tools
AC_PROG_INSTALL
AC_PROG_SED
PKG_PROG_PKG_CONFIG
LT_INIT

# Check for OpenGL
error_no_gl() {
    echo "------------------------------------------------------------"
    echo " OpenGL is needed to build MY_NAME."
    echo " Please visit 'http://opengl.org/'."
    echo "------------------------------------------------------------"
    (exit 1); exit 1;
}
if test "$host_vendor" != 'apple'; then
    AC_CHECK_HEADER([GL/gl.h], [], [error_no_gl], [])
    AC_CHECK_LIB([GL], [glGetString], [], [error_no_gl], [])
fi

# Check for GLFW
error_no_glfw() {
    AC_MSG_RESULT([no])
    echo "------------------------------------------------------------"
    echo " GLFW is needed to build MY_NAME."
    echo " Please visit 'http://glfw.org/'."
    echo "------------------------------------------------------------"
    (exit 1); exit 1;
}
AC_MSG_CHECKING([for GLFW])
PKG_CHECK_EXISTS([libglfw], [AC_MSG_RESULT([yes])], [error_no_glfw])
AC_DEFINE([GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED], [1], [Required for GLFW])

# Check for CppUnit
error_no_cppunit() {
    AC_MSG_RESULT([no])
    echo "------------------------------------------------------------"
    echo " CppUnit is needed to build MY_NAME."
    echo " Please visit 'http://cppunit.sourceforge.net/'."
    echo "------------------------------------------------------------"
    (exit 1); exit 1;
}
AC_MSG_CHECKING([for CppUnit])
PKG_CHECK_EXISTS([cppunit], [AC_MSG_RESULT([yes])], [error_no_cppunit])

# Define flags needed for OpenGL 3
if test "$host_vendor" = 'apple'; then
    AC_DEFINE([GL3_PROTOTYPES], [1], [Required for using OpenGL 3 on Mac])
else
    AC_DEFINE([GL_GLEXT_PROTOTYPES], [1], [Required for using OpenGL 3 on Linux])
fi

# Finish
AC_CONFIG_FILES(MY_TARNAME-MY_MAJOR_VERSION.pc [Makefile])
PKG_CHECK_MODULES([DEPS], libglfw cppunit)
AC_OUTPUT

# Report
echo \
"--------------------------------------------------------------
 ${PACKAGE_NAME} ${PACKAGE_VERSION}
 ${PACKAGE_DESCRIPTION}

 prefix      ${prefix}
 CXX         ${CXX}
 CPPFLAGS    ${CPPFLAGS}
 CXXFLAGS    ${CXXFLAGS}
 LDFLAGS     ${LDFLAGS}
 DEFS        ${DEFS}
 
 Now type 'make' then 'sudo make install'
--------------------------------------------------------------"
