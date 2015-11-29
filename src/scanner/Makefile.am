
# The libraries to build
noinst_LIBRARIES = libscanner.a

AM_CXXFLAGS  =-I$(top_srcdir)/src/scanner
AM_CXXFLAGS += $(GLIB_CXXFLAGS)
AM_CXXFLAGS += $(SQLITE3_CXXFLAGS)

if DEBUG
  AM_CXXFLAGS += -Wall -O3 -g
else
  AM_CXXFLAGS += -Wall -O3
endif

# The files to add to the library and to the source distribution
libscanner_a_SOURCES =      \
    $(databases_a_HEADERS)  \
    node.cpp

