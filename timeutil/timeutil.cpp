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

#include "timeutil.h"

#include <stdlib.h>
#include <stdio.h>

namespace timeutil
{

timeval makeTimeval(long sec, long usec)
{
	timeval t;
	t.tv_sec = sec;
	t.tv_usec = usec;
	return t;
}

std::string toString(const timeval& t)
{
	bool negative = (t.tv_sec < 0) || (t.tv_usec < 0);
	const char* sign = negative ? "-" : "";
	char buffer[32];
	sprintf(buffer, "%s%ld.%06ld", sign, labs(t.tv_sec), labs(t.tv_usec));
	return buffer;
}

} // namespace timeutil
