#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FretStorm], [0.1], [felix@piedallu.me])
AC_CONFIG_SRCDIR([src/fretstorm.cpp])
AM_INIT_AUTOMAKE

AM_SILENT_RULES([yes])


# Checks for programs. These may set default variables, such as CFLAGS
PKG_PROG_PKG_CONFIG
AC_PROG_CXX
AC_PROG_RANLIB

# Checks for libraries.
AX_BOOST_BASE([1.58],, [AC_MSG_ERROR([We needs Boost, but it was not found in your system])])
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM

PKG_CHECK_MODULES([GLIB], [gio-2.0])

PKG_CHECK_MODULES([SQLITE3], [sqlite3], [have_libsqlite3=yes], [have_libsqlite3=no])
AM_CONDITIONAL([LIB_SQLITE3],  [test "$have_libsqlite3" = "yes"])

#AC_CHECK_LIB(vsqlitepp, main, [], [AC_MSG_ERROR([vsqlite++ was not found !])])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Add debug support
AC_ARG_ENABLE(debug,
  AS_HELP_STRING(
    [--enable-debug],
    [enable debugging, default: no]),
    [case "${enableval}" in
      yes) debug=true ;;
      no)  debug=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
    esac],
    [debug=false])
AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
AM_COND_IF(DEBUG,
    AC_DEFINE(DEBUG, 1, [Define to 0 if this is a release build]),
    AC_DEFINE(DEBUG, 0, [Define to 1 or higher if this is a debug build]))


AC_CONFIG_FILES(Makefile
                src/Makefile
                src/scanner/Makefile
                )

AC_CONFIG_SUBDIRS([hand])

AC_OUTPUT


