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

#include "FpsCounter.h"

#include "timevalops.h"

namespace timeutil {

FpsCounter::FpsCounter() {
    reset();
}

FpsCounter::~FpsCounter() {
}

void FpsCounter::reset() {
    fps = 0.0f;
    frames = 0;

    prev.tv_sec = -1;
    prev.tv_usec = 0;

    elapsed.tv_sec = 0;
    elapsed.tv_usec = 0;
}

int FpsCounter::framesPerSec() const {
    return (int)(fps + 0.5f);
}

float FpsCounter::framesPerSecReal() const {
    return fps;
}

bool FpsCounter::update() {
    timeval now;
    gettimeofday(&now, 0);
    return update(now);
}

bool FpsCounter::update(const timeval& t) {
    if (prev.tv_sec < 0) {
        prev = t;
        return false;
    }

    frames++;
    timeval dt = t - prev;
    elapsed += dt;
    prev = t;

    bool changed = false;
    if (elapsed.tv_sec >= 1) {
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
