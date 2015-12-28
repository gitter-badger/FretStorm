## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = fretstorm

fretstorm_SOURCES = fretstorm.cpp   \
            scanner/node.cpp

AM_CXXFLAGS=-Wall -O3                   \
            $(GLIB_CXXFLAGS)            \
            $(SQLITE3_CXXFLAGS)         \
    -I$(top_srcdir)/src/midi            \
    -I$(top_srcdir)/src/scanner         \
    -DPACKAGE_SRC_DIR=\""$(srcdir)"\"

if DEBUG
  AM_CXXFLAGS += -g
endif

fretstorm_LDADD  = \
        $(top_builddir)/midifile/lib/libmidifile.a   \
        $(AM_LDFLAGS)               \
        $(BOOST_SYSTEM_LIB)         \
        $(BOOST_FILESYSTEM_LIB)     \
        $(SQLITE_LIBS)              \
        $(GLIB_LIBS)
