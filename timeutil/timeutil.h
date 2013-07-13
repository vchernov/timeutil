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

#ifndef TIMEUTIL_H_
#define TIMEUTIL_H_

#include <sys/time.h>
#include <stdio.h>
#include <string>

namespace timeutil
{

timeval makeTimeval(long sec, long usec);

timeval getCurrentTime();

/// Serializes timeval to file. 32 and 64 bit system independent.
void writeTimeval(FILE* file, const timeval& t);

/// Loads timeval from file, saved by using this library.
bool readTimeval(FILE* file, timeval& t);

/// Converts timeval to string in fixed-point format "sec.usec".
std::string toString(const timeval& t);

/**
 * Converts broken-down time structure to string according to specified format.
 *
 * @param brokenTime  The broken-down time.
 * @param fmt         The format of the expected string.
 * @param usec        The microseconds (optional).
 * @param usecSep     Separation character between the time and the microseconds (optional).
 * @return The string with date and time information.
 */
std::string toString(const tm& brokenTime, const char* fmt, //
	const long* usec = NULL, const char* usecSep = ".");

/*
 * Date and time format:
 * %s  The number of seconds since the Epoch
 * %a  Abbreviated weekday name               Thu
 * %A  Full weekday name                      Thursday
 * %b  Abbreviated month name                 Aug
 * %B  Full month name                        August
 * %c  Date and time representation           Thu Aug 23 14:55:02 2001
 * %d  Day of the month (01-31)               23
 * %H  Hour in 24h format (00-23)             14
 * %I  Hour in 12h format (01-12)             02
 * %j  Day of the year (001-366)              235
 * %m  Month as a decimal number (01-12)      08
 * %M  Minute (00-59)                         55
 * %p  AM or PM designation                   PM
 * %S  Second (00-61)                         02
 * %U  Week number with the first Sunday as the first day of week one (00-53)    33
 * %w  Weekday as a decimal number with Sunday as 0 (0-6)                        4
 * %W  Week number with the first Monday as the first day of week one (00-53)    34
 * %x  Date representation                    08/23/01
 * %X  Time representation                    14:55:02
 * %y  Year, last two digits (00-99)          01
 * %Y  Year                                   2001
 * %Z  Timezone name or abbreviation          CDT
 * %%  A % sign                               %
 */

/**
 * Parses date and time values from string.
 * The text should be in format "year[4].month[2].day[2] hour[2]:minute[2]:second[2].usec[6]".
 * The usec part is optional, all the other parameters are mandatory.
 * The separators can be any character.
 *
 * param[in]  str  The textual date and time.
 * param[out] t    The result of the parsing.
 * return Success or not.
 */
bool parseDateTime(const char* str, timeval& t);

} // namespace timeutil

#endif // TIMEUTIL_H_
