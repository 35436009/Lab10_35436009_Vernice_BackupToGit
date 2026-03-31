#include "WeatherRec.h"

// Default constructor.
WeatherRec::WeatherRec()
{
    m_date = Date();
    m_time = Time();
    m_speed = 0.0;
    m_solarRadiation = 0.0;
    m_temperature = 0.0;
    m_hasSpeed = false;
    m_hasSolar = false;
    m_hasTemp = false;
}

// Parameterized constructor.
WeatherRec::WeatherRec(const Date& date, const Time& time)
{
    m_date = date;
    m_time = time;
    m_speed = 0.0;
    m_solarRadiation = 0.0;
    m_temperature = 0.0;
    m_hasSpeed = false;
    m_hasSolar = false;
    m_hasTemp = false;
}

// Gets the date.
Date WeatherRec::GetDate() const
{
    return m_date;
}

// Sets the date.
void WeatherRec::SetDate(const Date& date)
{
    m_date = date;
}

// Gets the time.
Time WeatherRec::GetTime() const
{
    return m_time;
}

// Sets the time.
void WeatherRec::SetTime(const Time& time)
{
    m_time = time;
}

// Checks if wind speed value is valid.
bool WeatherRec::HasSpeed() const
{
    return m_hasSpeed;
}

// Gets wind speed.
double WeatherRec::GetSpeed() const
{
    return m_speed;
}

// Sets wind speed.
void WeatherRec::SetSpeed(double speed, bool valid)
{
    m_speed = speed;
    m_hasSpeed = valid;
}

// Checks if solar radiation value is valid.
bool WeatherRec::HasSolar() const
{
    return m_hasSolar;
}

// Gets solar radiation.
double WeatherRec::GetSolarRadiation() const
{
    return m_solarRadiation;
}

// Sets solar radiation.
void WeatherRec::SetSolarRadiation(double solar, bool valid)
{
    m_solarRadiation = solar;
    m_hasSolar = valid;
}

// Checks if temperature value is valid.
bool WeatherRec::HasTemp() const
{
    return m_hasTemp;
}

// Gets temperature.
double WeatherRec::GetTemperature() const
{
    return m_temperature;
}

// Sets temperature.
void WeatherRec::SetTemperature(double temperature, bool valid)
{
    m_temperature = temperature;
    m_hasTemp = valid;
}

// Compares two weather records by full timestamp.
bool WeatherRec::operator<(const WeatherRec& other) const
{
    if (m_date.GetYear() != other.m_date.GetYear())
        return m_date.GetYear() < other.m_date.GetYear();

    if (m_date.GetMonth() != other.m_date.GetMonth())
        return m_date.GetMonth() < other.m_date.GetMonth();

    if (m_date.GetDay() != other.m_date.GetDay())
        return m_date.GetDay() < other.m_date.GetDay();

    if (m_time.GetHour() != other.m_time.GetHour())
        return m_time.GetHour() < other.m_time.GetHour();

    return m_time.GetMinute() < other.m_time.GetMinute();
}

// Checks whether two records have the same full timestamp.
bool WeatherRec::operator==(const WeatherRec& other) const
{
    return m_date.GetYear() == other.m_date.GetYear() &&
           m_date.GetMonth() == other.m_date.GetMonth() &&
           m_date.GetDay() == other.m_date.GetDay() &&
           m_time.GetHour() == other.m_time.GetHour() &&
           m_time.GetMinute() == other.m_time.GetMinute();
}

// Compares two weather records by full timestamp.
bool WeatherRec::operator>(const WeatherRec& other) const
{
    return other < *this;
}

// Outputs a WeatherRec to a stream.
std::ostream& operator<<(std::ostream& os, const WeatherRec& rec)
{
    os << rec.GetDate().GetDay() << "/"
       << rec.GetDate().GetMonth() << "/"
       << rec.GetDate().GetYear() << " "
       << rec.GetTime().GetHour() << ":"
       << rec.GetTime().GetMinute();
    return os;
}
