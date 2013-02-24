# timeutil makefile

CXX = g++
LINKER = g++
AR = ar cr

prefix = /usr/local
exec_prefix = $(prefix)
includedir = $(prefix)/include
libdir = $(exec_prefix)/lib

CXXFLAGS = -Wall -Wextra -O2 -flto
LDFLAGS = -O2 -flto

timeutil_STATIC_LIB = libtimeutil.a
timetest_BIN = timetest

all: $(timeutil_STATIC_LIB) $(timetest_BIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# timeutil

timeutil_OBJ = timeutil.o

timeutil.o: timeutil.cpp timeutil.h

$(timeutil_STATIC_LIB): $(timeutil_OBJ)
	$(AR) $@ $(timeutil_OBJ)

# timetest

timetest_OBJ = timetest.o

timetest.o: timetest.cpp timeutil.h

$(timetest_BIN): $(timeutil_STATIC_LIB)
timetest_LIBS = -L. -ltimeutil

$(timetest_BIN): $(timetest_OBJ)
	$(LINKER) $(LDFLAGS) -o $@ $(timetest_OBJ) $(timetest_LIBS)

test: $(timetest_BIN)
	./$(timetest_BIN)

clean:
	rm -f $(timeutil_STATIC_LIB) $(timeutil_OBJ)
	rm -f $(timetest_BIN) $(timetest_OBJ)

install: $(timeutil_STATIC_LIB)
	cp timeutil.h $(includedir)
	cp $(timeutil_STATIC_LIB) $(libdir)

uninstall:
	rm -f $(includedir)/timeutil.h
	rm -f $(libdir)/$(timeutil_STATIC_LIB)

.PHONY: all clean install uninstall