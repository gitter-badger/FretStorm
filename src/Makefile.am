## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = fretstorm

fretstorm_SOURCES = fretstorm.cpp   \
            scanner/node.cpp        \
            midi/midi.cpp           \
            midi/event.cpp          \
            midi/song.cpp           \
            midi/track.cpp          \
            midi/midifile/Binasc.cpp        \
            midi/midifile/MidiEvent.cpp     \
            midi/midifile/MidiEventList.cpp \
            midi/midifile/MidiFile.cpp      \
            midi/midifile/MidiMessage.cpp

AM_CXXFLAGS=-Wall -O3 -g                \
            $(GLIB_CXXFLAGS)            \
            $(SQLITE3_CXXFLAGS)         \
    -I$(top_srcdir)/src/midi            \
    -I$(top_srcdir)/src/midi/midifile   \
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
