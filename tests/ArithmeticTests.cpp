#include <UnitTest++/UnitTest++.h>

#include "../timeutil/timeutil.h"
#include "../timeutil/timevalops.h"

#include <stdlib.h>

using namespace timeutil;

SUITE(Arithmetic)
{

TEST(Plus)
{
	for (long a = -3000000; a <= 3000000; a += 10000)
	{
		for (long b = -3000000; b <= 3000000; b += 10000)
		{
			timeval ta = makeTimeval(a / usecPerSec, a % usecPerSec);
			timeval tb = makeTimeval(b / usecPerSec, b % usecPerSec);
			timeval tr = ta + tb;

			CHECK(labs(tr.tv_usec) < usecPerSec);

			long long actual = labs(tr.tv_sec) * usecPerSec + labs(tr.tv_usec);
			if ((tr.tv_sec < 0) || (tr.tv_usec < 0))
				actual = -actual;

			long long expected = a + b;
			CHECK_EQUAL(expected, actual);
		}
	}
}

TEST(Minus)
{
	for (long a = -3000000; a <= 3000000; a += 10000)
	{
		for (long b = -3000000; b <= 3000000; b += 10000)
		{
			timeval ta = makeTimeval(a / usecPerSec, a % usecPerSec);
			timeval tb = makeTimeval(b / usecPerSec, b % usecPerSec);
			timeval tr = ta - tb;

			CHECK(labs(tr.tv_usec) < usecPerSec);

			long long actual = labs(tr.tv_sec) * usecPerSec + labs(tr.tv_usec);
			if ((tr.tv_sec < 0) || (tr.tv_usec < 0))
				actual = -actual;

			long long expected = a - b;
			CHECK_EQUAL(expected, actual);
		}
	}
}

}
