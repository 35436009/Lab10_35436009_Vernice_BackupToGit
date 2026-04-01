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

// Get the date.
const Date& WeatherRec::GetDate() const
{
    return m_date;
}

// Sets the date.
void WeatherRec::SetDate(const Date& date)
{
    m_date = date;
}

// Get the time.
const Time& WeatherRec::GetTime() const
{
    return m_time;
}

// Sets the time.
void WeatherRec::SetTime(const Time& time)
{
    m_time = time;
}

// Check whether wind speed is available.
bool WeatherRec::HasSpeed() const
{
    return m_hasSpeed;
}

// Gets wind speed.
double WeatherRec::GetSpeed() const
{
    return m_speed;
}

// Sets wind speed and validity.
void WeatherRec::SetSpeed(double speed, bool valid)
{
    m_speed = speed;
    m_hasSpeed = valid;
}

// Check whether solar radiation is available.
bool WeatherRec::HasSolar() const
{
    return m_hasSolar;
}

// Gets solar radiation.
double WeatherRec::GetSolarRadiation() const
{
    return m_solarRadiation;
}

// Sets solar radiation and validity.
void WeatherRec::SetSolarRadiation(double solar, bool valid)
{
    m_solarRadiation = solar;
    m_hasSolar = valid;
}

// Check whether temperature is available.
bool WeatherRec::HasTemp() const
{
    return m_hasTemp;
}

// Gets temperature.
double WeatherRec::GetTemperature() const
{
    return m_temperature;
}

// Sets temperature and validity.
void WeatherRec::SetTemperature(double temperature, bool valid)
{
    m_temperature = temperature;
    m_hasTemp = valid;
}

// Compares two weather records by timestamp.
bool WeatherRec::operator<(const WeatherRec& other) const
{
    if (m_date < other.m_date)
    {
        return true;
    }
    else if (m_date > other.m_date)
    {
        return false;
    }
    else
    {
        if (m_time < other.m_time)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// Checks whether two records have the same timestamp.
bool WeatherRec::operator==(const WeatherRec& other) const
{
    if (m_date == other.m_date)
    {
        if (m_time == other.m_time)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// Compares two weather records by timestamp.
bool WeatherRec::operator>(const WeatherRec& other) const
{
    if (m_date > other.m_date)
    {
        return true;
    }
    else if (m_date < other.m_date)
    {
        return false;
    }
    else
    {
        if (m_time > other.m_time)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// Outputs a weather record to a stream.
std::ostream& operator<<(std::ostream& os, const WeatherRec& rec)
{
    os << rec.GetDate() << " " << rec.GetTime();
    os << " Speed=" << rec.GetSpeed();
    os << " Solar=" << rec.GetSolarRadiation();
    os << " Temp=" << rec.GetTemperature();

    return os;
}
