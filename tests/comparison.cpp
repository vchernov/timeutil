#include <assert.h>

#include "../timeutil/timeutil.h"
#include "../timeutil/timevalops.h"

int main(int, char**)
{
	using namespace timeutil;

	// operators
	assert(makeTimeval(1, 2) == makeTimeval(1, 2));
	assert(makeTimeval(1, 2) != makeTimeval(0, 0));
	assert(makeTimeval(1, 2) < makeTimeval(1, 2) + makeTimeval(0, 1));
	assert(makeTimeval(1, 2) > makeTimeval(1, 2) - makeTimeval(0, 1));
	assert(makeTimeval(1, 2) <= makeTimeval(3, 4));
	assert(makeTimeval(1, 2) >= makeTimeval(1, 2));

	return 0;
}
