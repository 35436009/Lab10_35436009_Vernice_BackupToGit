#include "WeatherRec.h"

// Default constructor
WeatherRec::WeatherRec()
{
    m_speed = 0.0;
    m_solarRadiation = 0.0;
    m_temperature = 0.0;

    m_hasSpeed = false;
    m_hasSolar = false;
    m_hasTemp = false;
}

// Constructor with Date and Time
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

// Get Date
Date WeatherRec::GetDate() const
{
    return m_date;
}

// Set Date
void WeatherRec::SetDate(const Date & date)
{
    m_date = date;
}

// Get Time
Time WeatherRec::GetTime() const
{
    return m_time;
}

// Set Time
void WeatherRec::SetTime(const Time & time)
{
    m_time = time;
}

// Wind
bool WeatherRec::HasSpeed() const
{
    return m_hasSpeed;
}

// Get Speed
double WeatherRec::GetSpeed() const
{
    return m_speed;
}

// Set Speed
void WeatherRec::SetSpeed(double speed, bool valid)
{
    m_speed = speed;
    m_hasSpeed = valid;
}

// Solar Radiation
bool WeatherRec::HasSolar() const
{
    return m_hasSolar;
}

// Get Solar Radiation
double WeatherRec::GetSolarRadiation() const
{
    return m_solarRadiation;
}

// Set Solar Radiation
void WeatherRec::SetSolarRadiation(double solar, bool valid)
{
    m_solarRadiation = solar;
    m_hasSolar = valid;
}

// Temperature
bool WeatherRec::HasTemp() const
{
    return m_hasTemp;
}

// Get Temp
double WeatherRec::GetTemperature() const
{
    return m_temperature;
}

// Set Temp
void WeatherRec::SetTemperature(double temp, bool valid)
{
    m_temperature = temp;
    m_hasTemp = valid;
}

// Stream output so WeatherRec can be printed TestVector
std::ostream& operator<<(std::ostream& os, const WeatherRec& rec)
{
    os << rec.GetDate() << " " << rec.GetTime() << " | ";

    os << "Speed=";
    if (rec.HasSpeed())
    {
        os << rec.GetSpeed();
    }
    else
    {
        os << "N/A";
    }

    os << ", Solar=";
    if (rec.HasSolar())
    {
        os << rec.GetSolarRadiation();
    }
    else
    {
        os << "N/A";
    }

    os << ", Temp=";
    if (rec.HasTemp())
    {
        os << rec.GetTemperature();
    }
    else
    {
        os << "N/A";
    }

    return os;
}
