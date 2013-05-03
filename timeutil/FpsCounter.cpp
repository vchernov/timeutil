#include "FpsCounter.h"

#include "timevalops.h"

namespace timeutil
{

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
	gettimeofday(&now, 0);
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

} // namespace timeutil
