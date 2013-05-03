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

check_PROGRAMS = tests/comparison tests/arithmetic
TESTS = $(check_PROGRAMS)

tests_comparison_SOURCES = tests/comparison.cpp
tests_comparison_LDADD = libtimeutil.la

tests_arithmetic_SOURCES = tests/arithmetic.cpp
tests_arithmetic_LDADD = libtimeutil.la
