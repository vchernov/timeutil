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

#include "Timestamp.h"

#include "timevalops.h"

namespace timeutil
{

const Timestamp Timestamp::null = Timestamp(0, 0);

Timestamp Timestamp::now()
{
	return Timestamp(getCurrentTime());
}

bool Timestamp::parse(const std::string& str, Timestamp& t)
{
	return parseDateTime(str.c_str(), t.value);
}

Timestamp::Timestamp()
{
}

Timestamp::Timestamp(long sec, long usec)
{
	value = makeTimeval(sec, usec);
}

Timestamp::Timestamp(const timeval& value) :
	value(value)
{
}

bool Timestamp::operator==(const Timestamp& other) const
{
	return value == other.value;
}

bool Timestamp::operator!=(const Timestamp& other) const
{
	return value != other.value;
}

bool Timestamp::operator<(const Timestamp& other) const
{
	return value < other.value;
}

bool Timestamp::operator>(const Timestamp& other) const
{
	return value > other.value;
}

bool Timestamp::operator<=(const Timestamp& other) const
{
	return value <= other.value;
}

bool Timestamp::operator>=(const Timestamp& other) const
{
	return value >= other.value;
}

Timestamp& Timestamp::operator+=(const Timestamp& other)
{
	value += other.value;
	return *this;
}

Timestamp& Timestamp::operator-=(const Timestamp& other)
{
	value -= other.value;
	return *this;
}

const Timestamp Timestamp::operator+(const Timestamp& other) const
{
	return Timestamp(value + other.value);
}

const Timestamp Timestamp::operator-(const Timestamp& other) const
{
	return Timestamp(value - other.value);
}

long Timestamp::getSec() const
{
	return value.tv_sec;
}

void Timestamp::setSec(long sec)
{
	value.tv_sec = sec;
}

long Timestamp::getUsec() const
{
	return value.tv_usec;
}

void Timestamp::setUsec(long usec)
{
	value.tv_usec = usec;
}

time_t Timestamp::getEpoch() const
{
	return value.tv_sec;
}

double Timestamp::toDouble() const
{
	return timeval2double(value);
}

bool Timestamp::isNull() const
{
	return *this == Timestamp::null;
}

void Timestamp::write(FILE* f) const
{
	writeTimeval(f, value);
}

bool Timestamp::read(FILE* f)
{
	return readTimeval(f, value);
}

void Timestamp::getBrokenTimeGM(tm& brokenTime) const
{
	time_t timer = getEpoch();
#ifdef __WIN32__
	// less safe
	brokenTime = *gmtime(&timer);
#else
	gmtime_r(&timer, &brokenTime);
#endif
}

void Timestamp::getBrokenTimeLocal(tm& brokenTime) const
{
	time_t timer = getEpoch();
#ifdef __WIN32__
	// less safe
	brokenTime = *localtime(&timer);
#else
	localtime_r(&timer, &brokenTime);
#endif
}

std::string Timestamp::toStr() const
{
	return timeval2string(value);
}

std::string Timestamp::toStrTime() const
{
	return toStrTimeGM();
}

std::string Timestamp::toStrTimeGM() const
{
	tm brokenTime;
	getBrokenTimeGM(brokenTime);
	return time2string(brokenTime, "%H:%M:%S", &value.tv_usec, ".");
}

std::string Timestamp::toStrTimeLocal() const
{
	tm brokenTime;
	getBrokenTimeLocal(brokenTime);
	return time2string(brokenTime, "%H:%M:%S", &value.tv_usec, ".");
}

std::string Timestamp::toStrDateTime() const
{
	return toStrDateTimeGM();
}

std::string Timestamp::toStrDateTimeGM() const
{
	tm brokenTime;
	getBrokenTimeGM(brokenTime);
	return time2string(brokenTime, "%Y.%m.%d %H:%M:%S", &value.tv_usec, ".");
}

std::string Timestamp::toStrDateTimeLocal() const
{
	tm brokenTime;
	getBrokenTimeLocal(brokenTime);
	return time2string(brokenTime, "%Y.%m.%d %H:%M:%S", &value.tv_usec, ".");
}

} // namespace timeutil
