#include "timeutil.h"

#include <stdlib.h>
#include <stdio.h>

namespace timeutil
{

timeval makeTimeval(long sec, long usec)
{
	timeval t;
	t.tv_sec = sec;
	t.tv_usec = usec;
	return t;
}

std::string toString(const timeval& t)
{
	bool negative = (t.tv_sec < 0) || (t.tv_usec < 0);
	const char* sign = negative ? "-" : "";
	char buffer[32];
	sprintf(buffer, "%s%ld.%06ld", sign, labs(t.tv_sec), labs(t.tv_usec));
	return buffer;
}

} // namespace timeutil
