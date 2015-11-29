bin_PROGRAMS = fretstorm
fretstorm_SOURCES = fretstorm.cpp

AM_CXXFLAGS=-I$(top_srcdir)/src/scanner         \
            -I$(top_srcdir)/src/midi

AM_CXXFLAGS+= $(GLIB_CXXFLAGS)
AM_CXXFLAGS+= $(SQLITE3_CXXFLAGS)

if DEBUG
  AM_CXXFLAGS += -Wall -g -O3
else
  AM_CXXFLAGS += -Wall    -O3
endif

fretstorm_LDADD  = \
        $(top_builddir)/midifile/lib/libmidifile.a   \
        scanner/libscanner.a        \
        $(AM_LDFLAGS)				\
	    $(BOOST_SYSTEM_LIB) 		\
	    $(BOOST_FILESYSTEM_LIB)

fretstorm_LDADD += $(GLIB_LIBS)
fretstorm_LDADD += $(SQLITE_LIBS)
