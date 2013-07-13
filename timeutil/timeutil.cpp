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
#include <string.h>
#include <stdint.h>

namespace timeutil
{

timeval makeTimeval(long sec, long usec)
{
	timeval t;
	t.tv_sec = sec;
	t.tv_usec = usec;
	return t;
}

timeval getCurrentTime()
{
	timeval t;
	gettimeofday(&t, NULL);
	return t;
}

void writeTimeval(FILE* file, const timeval& t)
{
	int64_t sec;
	sec = t.tv_sec;
	fwrite(&sec, sizeof(sec), 1, file);

	int32_t usec;
	usec = t.tv_usec;
	fwrite(&usec, sizeof(usec), 1, file);
}

bool readTimeval(FILE* file, timeval& t)
{
	int64_t sec;
	int32_t usec;
	if (fread(&sec, sizeof(sec), 1, file) != 1)
		return false;
	if (fread(&usec, sizeof(usec), 1, file) != 1)
		return false;
	t.tv_sec = sec;
	t.tv_usec = usec;
	return true;
}

std::string toString(const timeval& t)
{
	bool negative = (t.tv_sec < 0) || (t.tv_usec < 0);
	const char* sign = negative ? "-" : "";
	char buffer[32];
	sprintf(buffer, "%s%ld.%06ld", sign, labs(t.tv_sec), labs(t.tv_usec));
	return buffer;
}

std::string toString(const tm& brokenTime, const char* fmt, const long* usec, const char* usecSep)
{
	char buffer[64];
	strftime(buffer, sizeof(buffer), fmt, &brokenTime);
	if (usec == NULL)
		return buffer;

	char bufferWithUsec[80];
	sprintf(bufferWithUsec, "%s%s%06ld", buffer, usecSep, *usec);
	return bufferWithUsec;
}

bool parseDateTime(const char* str, timeval& t)
{
	tm dateTime;
	memset(&dateTime, 0, sizeof(tm));

	long subSec;
	int filled = sscanf(str, "%04d%*c%02d%*c%02d%*c%02d%*c%02d%*c%02d%*c%06ld", //
		&dateTime.tm_year, &dateTime.tm_mon, &dateTime.tm_mday, //
		&dateTime.tm_hour, &dateTime.tm_min, &dateTime.tm_sec, //
		&subSec);
	if (filled < 6)
		return false;

	dateTime.tm_mon -= 1;
	dateTime.tm_year -= 1900;
	if (dateTime.tm_year < 70)
		dateTime.tm_year = 70;

	time_t sec;
	if (dateTime.tm_year == 70 && dateTime.tm_mon == 0 && dateTime.tm_mday == 1)
		sec = dateTime.tm_hour * 60 * 60 + dateTime.tm_min * 60 + dateTime.tm_sec;
	else
		sec = timegm(&dateTime);
	t.tv_sec = sec;

	if (filled == 7)
		t.tv_usec = subSec;
	else
		t.tv_usec = 0;
	return true;
}

} // namespace timeutil
