ACLOCAL_AMFLAGS = -I m4 --install
EXTRA_DIST = m4/NOTES

lib_LTLIBRARIES = libtimeutil.la

libtimeutil_la_SOURCES = \
	timeutil/timeutil.h \
	timeutil/timeutil.cpp \
	timeutil/timevalops.h \
	timeutil/timevalops.cpp \
	timeutil/FpsCounter.h \
	timeutil/FpsCounter.cpp \
	timeutil/Timestamp.h \
	timeutil/Timestamp.cpp

nobase_include_HEADERS = \
	timeutil/timeutil.h \
	timeutil/timevalops.h \
	timeutil/FpsCounter.h \
	timeutil/Timestamp.h

libtimeutil_la_LDFLAGS = -no-undefined \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

TESTS = tests/arithmetic tests/runAllTests
check_PROGRAMS = $(TESTS)

tests_arithmetic_SOURCES = tests/arithmetic.cpp
tests_arithmetic_LDADD = libtimeutil.la

tests_runAllTests_SOURCES = \
	tests/runAllTests.cpp \
	tests/Timestamp_test.cpp
tests_runAllTests_CXXFLAGS = $(CPPUNIT_CFLAGS)
tests_runAllTests_LDFLAGS = $(CPPUNIT_LIBS)
tests_runAllTests_LDADD = libtimeutil.la

.PHONY: check-norun
check-norun: $(check_PROGRAMS) 
