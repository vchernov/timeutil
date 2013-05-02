/**
 * @file timeutil.cpp
 * @date Feb 6, 2013
 * @author Vladimir Chernov <2chernov@gmail.com>
 */

#include "timeutil.h"
#include <stdlib.h>
#include <stdio.h>

// constructor

timeval makeTimeval(__time_t sec, __suseconds_t usec)
{
	timeval t;
	t.tv_sec = sec;
	t.tv_usec = usec;
	return t;
}

// 2string

std::string toString(const timeval& t)
{
	bool negative = (t.tv_sec < 0) || (t.tv_usec < 0);
	const char* sign = negative ? "-" : "";
	char buffer[32];
	sprintf(buffer, "%s%ld.%06ld", sign, labs(t.tv_sec), labs(t.tv_usec));
	return buffer;
}

// arithmetic

// calculate addition of positive arguments
void add(const timeval& a, const timeval& b, timeval& result);

// calculate subtraction of positive arguments, return true if the result is negative
bool sub(const timeval& a, const timeval& b, timeval& result);

timeval operator+(const timeval& a, const timeval& b)
{
	// is the a negative
	bool nega = (a.tv_sec < 0) || (a.tv_usec < 0);

	// absolute value of the a
	timeval absa;
	absa.tv_sec = labs(a.tv_sec);
	absa.tv_usec = labs(a.tv_usec);

	// is the b negative
	bool negb = (b.tv_sec < 0) || (b.tv_usec < 0);

	// absolute value of the b
	timeval absb;
	absb.tv_sec = labs(b.tv_sec);
	absb.tv_usec = labs(b.tv_usec);

	timeval result;
	bool negative; // sign of the result
	if (nega)
	{
		if (negb)
		{
			add(absa, absb, result);
			negative = true;
		}
		else
			negative = sub(absb, absa, result);
	}
	else
	{
		if (negb)
			negative = sub(absa, absb, result);
		else
		{
			add(absa, absb, result);
			negative = false;
		}
	}

	if (negative)
	{
		// making the result negative
		if (result.tv_sec != 0)
			result.tv_sec = -result.tv_sec;
		else
			result.tv_usec = -result.tv_usec;
	}
	return result;
}

timeval operator-(const timeval& a, const timeval& b)
{
	// is the a negative
	bool nega = (a.tv_sec < 0) || (a.tv_usec < 0);

	// absolute value of the a
	timeval absa;
	absa.tv_sec = labs(a.tv_sec);
	absa.tv_usec = labs(a.tv_usec);

	// is the b negative
	bool negb = (b.tv_sec < 0) || (b.tv_usec < 0);

	// absolute value of the b
	timeval absb;
	absb.tv_sec = labs(b.tv_sec);
	absb.tv_usec = labs(b.tv_usec);

	timeval result;
	bool negative; // sign of the result
	if (nega)
	{
		if (negb)
			negative = sub(absb, absa, result);
		else
		{
			add(absa, absb, result);
			negative = true;
		}
	}
	else
	{
		if (negb)
		{
			add(absa, absb, result);
			negative = false;
		}
		else
			negative = sub(absa, absb, result);
	}

	if (negative)
	{
		// making the result negative
		if (result.tv_sec != 0)
			result.tv_sec = -result.tv_sec;
		else
			result.tv_usec = -result.tv_usec;
	}
	return result;
}

void add(const timeval& a, const timeval& b, timeval& result)
{
	result.tv_sec = a.tv_sec + b.tv_sec;
	result.tv_usec = a.tv_usec + b.tv_usec;
	if (result.tv_usec >= 1000000)
	{
		result.tv_sec++;
		result.tv_usec -= 1000000;
	}
}

bool sub(const timeval& a, const timeval& b, timeval& result)
{
	bool negative;
	if (a.tv_sec > b.tv_sec)
	{
		negative = false;
		if (a.tv_usec >= b.tv_usec)
		{
			result.tv_sec = a.tv_sec - b.tv_sec;
			result.tv_usec = a.tv_usec - b.tv_usec;
		}
		else
		{
			result.tv_sec = a.tv_sec - b.tv_sec - 1;
			result.tv_usec = 1000000 - b.tv_usec + a.tv_usec;
		}
	}
	else if (a.tv_sec < b.tv_sec)
	{
		negative = true;
		if (a.tv_usec > b.tv_usec)
		{
			result.tv_sec = b.tv_sec - a.tv_sec - 1;
			result.tv_usec = 1000000 - a.tv_usec + b.tv_usec;
		}
		else
		{
			result.tv_sec = b.tv_sec - a.tv_sec;
			result.tv_usec = b.tv_usec - a.tv_usec;
		}
	}
	else
	{
		result.tv_sec = 0;
		if (a.tv_usec >= b.tv_usec)
		{
			negative = false;
			result.tv_usec = a.tv_usec - b.tv_usec;
		}
		else
		{
			negative = true;
			result.tv_usec = b.tv_usec - a.tv_usec;
		}
	}
	return negative;
}

timeval operator+=(timeval& a, const timeval& b)
{
	a = a + b;
	return a;
}

timeval operator-=(timeval& a, const timeval& b)
{
	a = a - b;
	return a;
}

// comparison

bool operator==(const timeval& a, const timeval& b)
{
	return (a.tv_sec == b.tv_sec) && (a.tv_usec == b.tv_usec);
}

bool operator!=(const timeval& a, const timeval& b)
{
	return (a.tv_sec != b.tv_sec) || (a.tv_usec != b.tv_usec);
}

bool operator<(const timeval& a, const timeval& b)
{
	if (a.tv_sec == b.tv_sec)
		return a.tv_usec < b.tv_usec;
	return a.tv_sec < b.tv_sec;
}

bool operator>(const timeval& a, const timeval& b)
{
	if (a.tv_sec == b.tv_sec)
		return a.tv_usec > b.tv_usec;
	return a.tv_sec > b.tv_sec;
}

bool operator<=(const timeval& a, const timeval& b)
{
	if (a.tv_sec == b.tv_sec)
		return a.tv_usec <= b.tv_usec;
	return a.tv_sec < b.tv_sec;
}

bool operator>=(const timeval& a, const timeval& b)
{
	if (a.tv_sec == b.tv_sec)
		return a.tv_usec >= b.tv_usec;
	return a.tv_sec > b.tv_sec;
}

// FpsCounter

FpsCounter::FpsCounter()
{
	reset();
}

FpsCounter::~FpsCounter()
{
}

void FpsCounter::reset()
{
	fps = 0.0f;
	frames = 0;

	prev.tv_sec = -1;
	prev.tv_usec = 0;

	elapsed.tv_sec = 0;
	elapsed.tv_usec = 0;
}

int FpsCounter::framesPerSec() const
{
	return (int)(fps + 0.5f);
}

float FpsCounter::framesPerSecReal() const
{
	return fps;
}

bool FpsCounter::update()
{
	timeval now;
	gettimeofday(&now, NULL);
	return update(now);
}

bool FpsCounter::update(const timeval& t)
{
	if (prev.tv_sec < 0)
	{
		prev = t;
		return false;
	}

	frames++;
	timeval dt = t - prev;
	elapsed += dt;
	prev = t;

	bool changed = false;
	if (elapsed.tv_sec >= 1)
	{
		int pfps = framesPerSec();
		float sec = elapsed.tv_sec + elapsed.tv_usec * 0.000001f;
		fps = frames / sec;
		changed = framesPerSec() != pfps;

		frames = 0;
		elapsed.tv_sec = 0;
		elapsed.tv_usec = 0;
	}
	return changed;
}
