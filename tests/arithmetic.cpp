#include <assert.h>
#include <stdlib.h>
#include <iostream>

#include "../timeutil/timeutil.h"
#include "../timeutil/timevalops.h"

int main(int, char**)
{
	using namespace timeutil;

	// current time
	timeval now;
	gettimeofday(&now, NULL);
	std::cout << "current time: " << toString(now) << std::endl;

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

	return 0;
}
