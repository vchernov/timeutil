#ifndef TIMEVALOPS_H_
#define TIMEVALOPS_H_

#include <sys/time.h>

namespace timeutil
{

// arithmetic operators

timeval operator+(const timeval& a, const timeval& b);
timeval operator-(const timeval& a, const timeval& b);

timeval operator+=(timeval& a, const timeval& b);
timeval operator-=(timeval& a, const timeval& b);

// comparison operators

bool operator==(const timeval& a, const timeval& b);
bool operator!=(const timeval& a, const timeval& b);

bool operator<(const timeval& a, const timeval& b);
bool operator>(const timeval& a, const timeval& b);

bool operator<=(const timeval& a, const timeval& b);
bool operator>=(const timeval& a, const timeval& b);

} // namespace timeutil

#endif // TIMEVALOPS_H_
