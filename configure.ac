## Copyright (c) 2015-  Félix Piédallu <felix@piedallu.me>
##
## This file is part of FretStorm.
##
## FretStorm is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by the
## Free Software Foundation, either version 2 of the License, or
## (at your option) any later version.
##
## FretStorm is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
## See the GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License along
## with this program.  If not, see <http://www.gnu.org/licenses/>.

dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_PREREQ([2.69])
AC_INIT([FretStorm], [0.1],  [https://github.com/salamandar/fretstorm/issues],
        [fretstorm],         [https://github.com/salamandar/fretstorm])

# AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/fretstorm.cpp])
AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

dnl ================================================================
dnl Check for Programs
dnl ================================================================
PKG_PROG_PKG_CONFIG

dnl ================================================================
dnl C++11 support
dnl ================================================================

AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11


dnl ================================================================
dnl Libraries
dnl ================================================================

LT_INIT
AX_BOOST_BASE([1.58],, [AC_MSG_ERROR([We needs Boost, but it was not found in your system])])
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM

PKG_CHECK_MODULES([GLIB], [gio-2.0])

PKG_CHECK_MODULES([SQLITE3], [sqlite3], [have_libsqlite3=yes], [have_libsqlite3=no])
AM_CONDITIONAL([LIB_SQLITE3],  [test "$have_libsqlite3" = "yes"])


dnl ================================================================
dnl Add Debug support
dnl ================================================================
AC_ARG_ENABLE(debug,
  AS_HELP_STRING([--enable-debug], [enable debugging, default: no]),
  [case "${enableval}" in
    yes) debug=true ;;
    no)  debug=false ;;
    *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
  esac],
  [debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
AM_COND_IF(DEBUG, AC_DEFINE(DEBUG, 1, [Define to 0 if this is a release build]),
                  AC_DEFINE(DEBUG, 0, [Define to 1 or higher if this is a debug build]))



AC_CONFIG_FILES(Makefile
                src/Makefile
                )

AC_CONFIG_SUBDIRS([hand])

AC_OUTPUT


