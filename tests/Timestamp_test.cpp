#include "../timeutil/Timestamp.h"

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

using namespace timeutil;

class TimestampTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TimestampTest);
	CPPUNIT_TEST(testComparison);
	CPPUNIT_TEST(testToString);
	CPPUNIT_TEST(testFromString);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp()
	{
		t1 = Timestamp(1, 2);
		t2 = Timestamp(3, 4);
		zero = Timestamp::null;
		now = Timestamp::now();
	}

	void tearDown()
	{
	}

	void testComparison()
	{
		CPPUNIT_ASSERT(t1 == t1);
		CPPUNIT_ASSERT(t1 != t2);

		CPPUNIT_ASSERT(t1 < t2);
		CPPUNIT_ASSERT(t1 <= t2);
		CPPUNIT_ASSERT(t1 <= t1);

		CPPUNIT_ASSERT(t2 > t1);
		CPPUNIT_ASSERT(t2 >= t1);
		CPPUNIT_ASSERT(t1 >= t1);
	}

	void testToString()
	{
		CPPUNIT_ASSERT_EQUAL(std::string("00:00:00.000000"), zero.toStrTimeGM());
		CPPUNIT_ASSERT_EQUAL(std::string("1970.01.01 00:00:00.000000"), zero.toStrDateTimeGM());
		CPPUNIT_ASSERT_EQUAL(std::string("00:00:01.000002"), t1.toStrTimeGM());
		CPPUNIT_ASSERT_EQUAL(std::string("3.000004"), t2.toStr());
	}

	void testFromString()
	{
		Timestamp t;
		CPPUNIT_ASSERT(Timestamp::parse("1988.01.18 12:34:56.789000", t));
		CPPUNIT_ASSERT(Timestamp::parse("0000.00.00 00:00:00", t));
		CPPUNIT_ASSERT(!Timestamp::parse("fake", t));
		CPPUNIT_ASSERT(Timestamp::parse(now.toStrDateTime(), t));
		CPPUNIT_ASSERT(now == t);
	}

private:
	Timestamp t1;
	Timestamp t2;
	Timestamp zero;
	Timestamp now;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TimestampTest);
