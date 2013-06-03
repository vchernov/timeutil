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

#include <stdint.h>
#include <string.h>

#include "timevalops.h"

namespace timeutil
{

const long Timestamp::usecPerSec = 1000000;
const double Timestamp::usec2sec = 1.0 / 1000000.0;

const Timestamp Timestamp::null = Timestamp(0, 0);

Timestamp Timestamp::now()
{
	Timestamp t;
	gettimeofday(&t.value, NULL);
	return t;
}

bool Timestamp::parseDateTime(const char* str, Timestamp& t)
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
	t.setSec(sec);

	if (filled == 7)
		t.setUsec(subSec);
	else
		t.setUsec(0);
	return true;
}

Timestamp::Timestamp()
{
}

Timestamp::Timestamp(long sec, long usec)
{
	value.tv_sec = sec;
	value.tv_usec = usec;
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
	return Timestamp(*this) += other;
}

const Timestamp Timestamp::operator-(const Timestamp& other) const
{
	return Timestamp(*this) -= other;
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
	double t = (double)value.tv_sec;
	t += (double)value.tv_usec * usec2sec;
	return t;
}

bool Timestamp::isNull() const
{
	return (value.tv_sec == 0) && (value.tv_usec == 0);
}

void Timestamp::write(FILE* f) const
{
	// must be no difference in 32 and 64 bit systems

	int64_t sec;
	sec = value.tv_sec;
	fwrite(&sec, sizeof(sec), 1, f);

	int32_t usec;
	usec = value.tv_usec;
	fwrite(&usec, sizeof(usec), 1, f);
}

bool Timestamp::read(FILE* f)
{
	// must be no difference in 32 and 64 bit systems
	int64_t sec;
	int32_t usec;
	if (fread(&sec, sizeof(sec), 1, f) != 1)
		return false;
	if (fread(&usec, sizeof(usec), 1, f) != 1)
		return false;
	value.tv_sec = sec;
	value.tv_usec = usec;
	return true;
}

void Timestamp::getBrokenTimeGM(tm& brokenTime) const
{
	time_t timer = getEpoch();
	gmtime_r(&timer, &brokenTime);
}

void Timestamp::getBrokenTimeLocal(tm& brokenTime) const
{
	time_t timer = getEpoch();
	localtime_r(&timer, &brokenTime);
}

std::string Timestamp::toStr(const tm& brokenTime, const char* fmt, const long* usec, const char* usecSep)
{
	char buffer[64];
	strftime(buffer, sizeof(buffer), fmt, &brokenTime);
	if (usec != NULL)
	{
		char bufferExt[80];
		sprintf(bufferExt, "%s%s%06ld", buffer, usecSep, *usec);
		return bufferExt;
	}
	else
		return buffer;
}

std::string Timestamp::toStr() const
{
	return toString(value);
}

std::string Timestamp::toStrTime() const
{
	return toStrTimeGM();
}

std::string Timestamp::toStrTimeGM() const
{
	tm brokenTime;
	getBrokenTimeGM(brokenTime);
	return Timestamp::toStr(brokenTime, "%H:%M:%S", &value.tv_usec, ".");
}

std::string Timestamp::toStrTimeLocal() const
{
	tm brokenTime;
	getBrokenTimeLocal(brokenTime);
	return Timestamp::toStr(brokenTime, "%H:%M:%S", &value.tv_usec, ".");
}

std::string Timestamp::toStrDateTime() const
{
	return toStrDateTimeGM();
}

std::string Timestamp::toStrDateTimeGM() const
{
	tm brokenTime;
	getBrokenTimeGM(brokenTime);
	return Timestamp::toStr(brokenTime, "%Y.%m.%d %H:%M:%S", &value.tv_usec, ".");
}

std::string Timestamp::toStrDateTimeLocal() const
{
	tm brokenTime;
	getBrokenTimeLocal(brokenTime);
	return Timestamp::toStr(brokenTime, "%Y.%m.%d %H:%M:%S", &value.tv_usec, ".");
}

} // namespace timeutil
