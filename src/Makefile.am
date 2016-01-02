## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = fretstorm

fretstorm_SOURCES = fretstorm.cpp   \
            scanner/node.cpp        \
            midi/BinUtils.cpp       \
            midi/MidiEvent.cpp      \
            midi/MidiFile.cpp       \
            midi/MidiTrack.cpp      \
            midi/midi.cpp

AM_CXXFLAGS=-Wall -O3 -g -std=gnu++11   \
            $(GLIB_CXXFLAGS)            \
            $(SQLITE3_CXXFLAGS)         \
    -I$(top_srcdir)/src/midi            \
    -I$(top_srcdir)/src/scanner         \
    -I$(top_builddir)/midifile/include  \
    -DPACKAGE_SRC_DIR=\""$(srcdir)"\"

if DEBUG
  AM_CXXFLAGS += -g
endif

fretstorm_LDADD  = \
        $(AM_LDFLAGS)               \
        $(BOOST_SYSTEM_LIB)         \
        $(BOOST_FILESYSTEM_LIB)     \
        $(SQLITE_LIBS)
