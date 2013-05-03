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
