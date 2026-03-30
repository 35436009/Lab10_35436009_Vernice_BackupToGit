#include "Time.h"

// Default constructor
Time::Time()
{
    m_hour = 0;
    m_minute = 0;
}

// Parameterized constructor
Time::Time(int hour, int minute)
{
    m_hour = hour;
    m_minute = minute;
}

// Get Hour
int Time::GetHour() const
{
    return m_hour;
}

// Set Hour
void Time::SetHour(int hour)
{
    m_hour = hour;
}

// Get Minute
int Time::GetMinute() const
{
    return m_minute;
}

// Set Minute
void Time::SetMinute(int minute)
{
    m_minute = minute;
}

// Output operator
ostream & operator<<(ostream & os, const Time & time)
{
    os << time.GetHour() << ":"
       << time.GetMinute();

    return os;
}

// Input operator
istream & operator>>(istream & input, Time & time)
{
    int hour, minute;
    char colon;

    input >> hour >> colon >> minute;

    time.SetHour(hour);
    time.SetMinute(minute);

    return input;
}
