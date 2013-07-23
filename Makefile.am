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

TESTS = tests/runAllTests
check_PROGRAMS = $(TESTS)

tests_runAllTests_SOURCES = \
	tests/runAllTests.cpp \
	tests/ArithmeticTests.cpp \
	tests/StringTests.cpp \
	tests/OperatorTests.cpp
	
tests_runAllTests_LDADD = libtimeutil.la -lUnitTest++

.PHONY: check-norun
check-norun: $(check_PROGRAMS) 
