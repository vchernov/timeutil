#include <UnitTest++/UnitTest++.h>

#include "../timeutil/Timestamp.h"

using namespace timeutil;

SUITE(Operator)
{

struct OperatorFixture
{
	OperatorFixture()
	{
		t1 = Timestamp(1, 2);
		t2 = Timestamp(3, 4);
	}

	Timestamp t1;
	Timestamp t2;
};

TEST_FIXTURE(OperatorFixture, Comparison)
{
	CHECK(t1 == t1);
	CHECK(t1 != t2);

	CHECK(t1 < t2);
	CHECK(t1 <= t2);
	CHECK(t1 <= t1);

	CHECK(t2 > t1);
	CHECK(t2 >= t1);
	CHECK(t1 >= t1);
}

}
