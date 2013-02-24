/**
 * @file timeutil.h
 * @date Feb 6, 2013
 * @author Vladimir Chernov <2chernov@gmail.com>
 */

#include <sys/time.h>
#include <string>

#ifndef TIMEUTIL_H_
#define TIMEUTIL_H_

// arithmetic

timeval operator+(const timeval& a, const timeval& b);
timeval operator-(const timeval& a, const timeval& b);

timeval operator+=(timeval& a, const timeval& b);
timeval operator-=(timeval& a, const timeval& b);

// comparison

bool operator==(const timeval& a, const timeval& b);
bool operator!=(const timeval& a, const timeval& b);

bool operator<(const timeval& a, const timeval& b);
bool operator>(const timeval& a, const timeval& b);

bool operator<=(const timeval& a, const timeval& b);
bool operator>=(const timeval& a, const timeval& b);

// 2string

std::string toString(const timeval& t);

/**
 * Frames Per Second counter.
 */
class FpsCounter
{
public:
	FpsCounter();
	virtual ~FpsCounter();

public:
	/// Set to initial state.
	void reset();

	/// Get counted FPS rounded to integer.
	int framesPerSec() const;

	/// Get counted FPS.
	float framesPerSecReal() const;

	/**
	 * Recalculate values using the current time.
	 * This function should be invoked every iteration.
	 * return Has the FPS been changed or not.
	 */
	bool update();

	/**
	 * Update by external time value.
	 * param[in] t The time of current iteration provided by user code.
	 * return Has the FPS been changed or not.
	 */
	bool update(const timeval& t);

private:
	timeval prev;
	timeval elapsed;
	size_t frames;
	float fps;
};

#endif /* TIMEUTIL_H_ */
