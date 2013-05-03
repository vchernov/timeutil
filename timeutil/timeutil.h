#ifndef TIMEUTIL_H_
#define TIMEUTIL_H_

#include <sys/time.h>
#include <string>

namespace timeutil
{

timeval makeTimeval(long sec, long usec);

std::string toString(const timeval& t);

} // namespace timeutil

#endif // TIMEUTIL_H_
