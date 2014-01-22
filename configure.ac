AC_PREREQ([2.68])
AC_INIT([timeutil], [0.1])
AC_CONFIG_SRCDIR([timeutil/timeutil.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.11 -Wall -Werror no-define foreign subdir-objects])

LT_CURRENT=0
LT_REVISION=0
LT_AGE=0
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_LIBTOOL
AC_LIBTOOL_WIN32_DLL

# Checks for libraries.
PKG_PROG_PKG_CONFIG([0.26])
PKG_CHECK_MODULES([UNITTEST], [unittest++ >= 1.3.0])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h sys/time.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_INT32_T
AC_TYPE_INT64_T

# Checks for library functions.
AC_FUNC_MKTIME
AC_CHECK_FUNCS([gettimeofday localtime_r memset])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
