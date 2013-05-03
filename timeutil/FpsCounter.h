#ifndef FPSCOUNTER_H_
#define FPSCOUNTER_H_

#include <sys/time.h>

namespace timeutil
{

/**
 * Frames Per Second counter.
 */
class FpsCounter
{
public:
	FpsCounter();
	virtual ~FpsCounter();

public:
	/// Sets to initial state.
	void reset();

	/// Gets counted FPS rounded to nearest integer.
	int framesPerSec() const;

	/// Gets counted FPS.
	float framesPerSecReal() const;

	/**
	 * Recalculates counter by using the current system time.
	 * This function should be invoked every iteration.
	 * return Has the FPS been changed or not.
	 */
	bool update();

	/**
	 * Recalculates counter by using external time value.
	 * param[in] t The time of current iteration provided by user code.
	 * return Has the FPS been changed or not.
	 */
	bool update(const timeval& t);

private:
	timeval prev;
	timeval elapsed;
	int frames;
	float fps;
};

} // namespace timeutil

#endif // FPSCOUNTER_H_
