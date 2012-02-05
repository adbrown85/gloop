# Check for Autoconf
AC_PREREQ([2.67])

# Initialize package information
define([MY_NAME], [Glycerin])
define([MY_MAJOR_VERSION], [0])
define([MY_MINOR_VERSION], [1])
define([MY_VERSION], MY_MAJOR_VERSION.MY_MINOR_VERSION)
define([MY_EMAIL], [adb1413@rit.edu])
define([MY_TARNAME], [glycerin])
define([MY_URL], [http://github.com/adbrown85/glycerin])
define([MY_DESCRIPTION], ['Fuel for OpenGL applications'])
AC_INIT(MY_NAME, MY_VERSION, MY_EMAIL, MY_TARNAME, MY_URL)
AC_CONFIG_SRCDIR([src/glycerin/common.h])
AC_CONFIG_HEADERS([config.h])
AC_SUBST([PACKAGE_MAJOR_VERSION], MY_MAJOR_VERSION)
AC_SUBST([PACKAGE_MINOR_VERSION], MY_MINOR_VERSION)
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

# Check for OpenGL
error_no_gl() {
    echo "no"
    echo "--------------------"
    echo " No OpenGL!"
    echo "--------------------"
    (exit 1); exit 1;
}
if test "$host_vendor" != 'apple'; then
    AC_SEARCH_LIBS([glGetString], [GL], , [error_no_gl])
    AC_CHECK_HEADER([GL/gl.h], , [error_no_gl])
fi

# Check for backend
if test "$host_vendor" = 'apple'; then
    AC_LANG_PUSH([Objective C++])
    AC_CHECK_HEADER(
        [Cocoa/Cocoa.h],
        [AC_DEFINE([HAVE_COCOA], [1], [Define to 1 if have Cocoa.])])
    LDFLAGS="-framework Cocoa -framework OpenGL"
    AC_LANG_POP()
else
    AC_CHECK_HEADER(
        [GL/glx.h],
        [AC_DEFINE([HAVE_GLX], [1], [Define to 1 if have GLX.])])
    LIBS="${LIBS} -lX11"
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
AC_CHECK_HEADER([GL/glfw.h], , [error_no_glfw])
AC_CHECK_LIB([glfw], glfwInit, , [error_no_glfw])

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

# Finish
AC_CONFIG_FILES(MY_TARNAME.pc [Makefile])
PKG_CHECK_MODULES([DEPS], cppunit)
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
 LIBS        ${LIBS}
 DEFS        ${DEFS}
 
 Now type 'make' then 'sudo make install'
--------------------------------------------------------------"
