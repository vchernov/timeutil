ACLOCAL_AMFLAGS = -I m4 --install
EXTRA_DIST = m4/NOTES

lib_LTLIBRARIES = libtimeutil.la

libtimeutil_la_SOURCES = \
	timeutil/timeutil.h \
	timeutil/timeutil.cpp \
	timeutil/timevalops.h \
	timeutil/timevalops.cpp \
	timeutil/FpsCounter.h \
	timeutil/FpsCounter.cpp

nobase_include_HEADERS = \
	timeutil/timeutil.h \
	timeutil/timevalops.h \
	timeutil/FpsCounter.h

check_PROGRAMS = tests/timetest
TESTS = $(check_PROGRAMS)

tests_timetest_SOURCES = tests/timetest.cpp
tests_timetest_LDADD = libtimeutil.la
