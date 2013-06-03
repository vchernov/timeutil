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

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <stdio.h>
#include <string>

#include "timeutil.h"

namespace timeutil
{

/**
 * Time stamp in microsecond precision (one millionth of second).
 */
class Timestamp
{
public:
	/// 0 time.
	static const Timestamp null;

	/// Obtain current system time in UTC.
	static Timestamp now();

	/**
	 * Parse date and time values from string.
	 * The text should be in format "year[4].month[2].day[2] hour[2]:minute[2]:second[2].usec[6]".
	 * The usec part is not mandatory, all the other parameters must be included.
	 * The separators can be any character.
	 *
	 * param[in]  str  Textual date and time.
	 * param[out] ts   Result of the parsing.
	 * return Success or not.
	 */
	static bool parseDateTime(const char* str, Timestamp& t);

	/**
	 * @brief Default constructor.
	 * @note Doesn't clear internal variables for performance reason.
	 * Use the \link Timestamp::null \endlink if 0 time is required.
	 */
	Timestamp();

	/**
	 * @brief Constructor with exact time values.
	 * @param sec Amount of seconds.
	 * @param usec Amount of microseconds.
	 */
	Timestamp(long sec, long usec = 0);

	bool operator==(const Timestamp& other) const;
	bool operator!=(const Timestamp& other) const;
	bool operator<(const Timestamp& other) const;
	bool operator>(const Timestamp& other) const;
	bool operator<=(const Timestamp& other) const;
	bool operator>=(const Timestamp& other) const;

	Timestamp& operator+=(const Timestamp& other);
	Timestamp& operator-=(const Timestamp& other);

	const Timestamp operator+(const Timestamp& other) const;
	const Timestamp operator-(const Timestamp& other) const;

	long getSec() const;
	void setSec(long sec);

	long getUsec() const;
	void setUsec(long usec);

	/// Get seconds since the Unix Epoch (1970.01.01 00:00:00 UTC).
	time_t getEpoch() const;

	double toDouble() const;

	bool isNull() const;

	/// Serialization to file.
	void write(FILE* f) const;

	/// Loading from file.
	bool read(FILE* f);

	/// Get Greenwich Mean broken-down time.
	void getBrokenTimeGM(tm& brokenTime) const;

	/// Get local broken-down time.
	void getBrokenTimeLocal(tm& brokenTime) const;

	/// Convert to string in fixed-point format "sec.usec".
	std::string toStr() const;

	/// Convert to string in format "hour:minute:second.usec".
	std::string toStrTime() const;

	/// Convert to string in format "hour:minute:second.usec" using Greenwich Mean time zone.
	std::string toStrTimeGM() const;

	/// Convert to string in format "hour:minute:second.usec" using local time zone.
	std::string toStrTimeLocal() const;

	/// Convert to string in format "year.month.day hour:minute:second.usec".
	std::string toStrDateTime() const;

	/// Convert to string in format "year.month.day hour:minute:second.usec" using Greenwich Mean time zone.
	std::string toStrDateTimeGM() const;

	/// Convert to string in format "year.month.day hour:minute:second.usec" using local time zone.
	std::string toStrDateTimeLocal() const;

private:
	// amount of microseconds per one second (the value is 1^6 = 1000000)
	static const long usecPerSec;

	// coefficient to convert microseconds to decimal seconds
	static const double usec2sec;

	static std::string toStr(const tm& brokenTime, const char* fmt, //
		const long* usec = NULL, const char* usecSep = ".");

	timeval value;
};

} // namespace timeutil

#endif // TIMESTAMP_H_
