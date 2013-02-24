/**
 * @file timeutil.h
 * @date Feb 6, 2013
 * @author Vladimir Chernov <2chernov@gmail.com>
 */

#include <time.h>
#include <string>

#ifndef TIMEUTIL_H_
#define TIMEUTIL_H_

// arithmetic

timeval operator+(const timeval& a, const timeval& b);
timeval operator-(const timeval& a, const timeval& b);

// comparison

bool operator==(const timeval& a, const timeval& b);
bool operator!=(const timeval& a, const timeval& b);

bool operator<(const timeval& a, const timeval& b);
bool operator>(const timeval& a, const timeval& b);

bool operator<=(const timeval& a, const timeval& b);
bool operator>=(const timeval& a, const timeval& b);

// 2string

std::string toString(const timeval& t);

#endif /* TIMEUTIL_H_ */
