/*
 * Copyright (C) 2013 Vladimir Chernov
 *
 * This file is part of timeutil library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FPSCOUNTER_H_
#define FPSCOUNTER_H_

#include <sys/time.h>

namespace timeutil {

/**
 * Frames Per Second counter.
 */
class FpsCounter {
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
     * Recalculates the counter by using the current system time.
     * This function should be invoked every iteration.
     * return Has the FPS been changed or not.
     */
    bool update();

    /**
     * Recalculates the counter by using external time value.
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
