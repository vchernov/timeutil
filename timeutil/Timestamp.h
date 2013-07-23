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
	 * Parses time stamp from string.
	 * @param[in]  str  Textual date and time.
	 * @param[out] t    Result of the parsing.
	 * @return Success or not.
	 */
	static bool parse(const std::string& str, Timestamp& t);

	/**
	 * @brief Default constructor.
	 * @note Doesn't clear internal variables for performance reason.
	 * Use the \link Timestamp::null \endlink if 0 time is required.
	 */
	Timestamp();

	/**
	 * Constructor from number of seconds and microseconds.
	 * @param sec   Amount of seconds.
	 * @param usec  Amount of microseconds.
	 */
	Timestamp(long sec, long usec = 0);

	/// Constructor from time value.
	Timestamp(const timeval& value);

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

	/// Gets seconds since the Unix Epoch (1970.01.01 00:00:00 UTC).
	time_t getEpoch() const;

	double toDouble() const;

	bool isNull() const;

	/// Serializes to file.
	void write(FILE* f) const;

	/// Loads from file.
	bool read(FILE* f);

	/// Gets Greenwich Mean broken-down time.
	void getBrokenTimeGM(tm& brokenTime) const;

	/// Gets local broken-down time.
	void getBrokenTimeLocal(tm& brokenTime) const;

	/// Converts to string in format "sec.usec".
	std::string toStr() const;

	/// Converts to string in format "hour:minute:second.usec".
	std::string toStrTime() const;

	/// Converts to string in format "hour:minute:second.usec" using Greenwich Mean time zone.
	std::string toStrTimeGM() const;

	/// Converts to string in format "hour:minute:second.usec" using local time zone.
	std::string toStrTimeLocal() const;

	/// Converts to string in format "year.month.day hour:minute:second.usec".
	std::string toStrDateTime() const;

	/// Converts to string in format "year.month.day hour:minute:second.usec" using Greenwich Mean time zone.
	std::string toStrDateTimeGM() const;

	/// Converts to string in format "year.month.day hour:minute:second.usec" using local time zone.
	std::string toStrDateTimeLocal() const;

	/// The time value.
	timeval value; // there is no reason to make it private
};

} // namespace timeutil

#endif // TIMESTAMP_H_
