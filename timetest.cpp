/**
 * @file timetest.cpp
 * @date Feb 6, 2013
 * @author Vladimir Chernov <2chernov@gmail.com>
 */

#include "timeutil.h"
#include <stdlib.h>
#include <iostream>
#include <assert.h>

int main(int, char**)
{
	std::cout << "start time test" << std::endl;

	// current time
	timeval now;
	gettimeofday(&now, NULL);
	std::cout << "current time: " << toString(now) << std::endl;

	// operators
	assert(makeTimeval(1, 2) == makeTimeval(1, 2));
	assert(makeTimeval(1, 2) != makeTimeval(0, 0));
	assert(makeTimeval(1, 2) < makeTimeval(1, 2) + makeTimeval(0, 1));
	assert(makeTimeval(1, 2) > makeTimeval(1, 2) - makeTimeval(0, 1));
	assert(makeTimeval(1, 2) <= makeTimeval(3, 4));
	assert(makeTimeval(1, 2) >= makeTimeval(1, 2));

	// arithmetic
	for (long a = -3000000; a <= 3000000; a += 10000)
	{
		for (long b = -3000000; b <= 3000000; b += 10000)
		{
			timeval ta = makeTimeval(a / 1000000, a % 1000000);
			timeval tb = makeTimeval(b / 1000000, b % 1000000);

			timeval tp = ta + tb;
			long long pr = labs(tp.tv_sec) * 1000000 + labs(tp.tv_usec);
			if ((tp.tv_sec < 0) || (tp.tv_usec < 0))
				pr = -pr;
			long long p = a + b;
			assert(p == pr);
			assert(labs(tp.tv_usec) < 1000000);

			timeval tm = ta - tb;
			long long mr = labs(tm.tv_sec) * 1000000 + labs(tm.tv_usec);
			if ((tm.tv_sec < 0) || (tm.tv_usec < 0))
				mr = -mr;
			long long m = a - b;
			assert(m == mr);
			assert(labs(tm.tv_usec) < 1000000);
		}
	}

	std::cout << "time test complete" << std::endl;
	return 0;
}
