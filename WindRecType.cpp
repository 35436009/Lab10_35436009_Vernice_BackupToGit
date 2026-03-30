#include "WindRecType.h"

// Default constructor
WindRecType::WindRecType()
{
    m_speed = 0.0;
}

// Parameterised constructor
WindRecType::WindRecType(const Date& date, const Time& time, double speed)
{
    m_date = date;
    m_time = time;
    m_speed = speed;
}

// Set date
void WindRecType::SetDate(const Date& date)
{
    m_date = date;
}

// Set time
void WindRecType::SetTime(const Time& time)
{
    m_time = time;
}

// Set speed (m/s)
void WindRecType::SetSpeed(double speed)
{
    if (speed < 0)
        speed = 0;

    m_speed = speed;
}

// Get date
Date WindRecType::GetDate() const
{
    return m_date;
}

// Get time
Time WindRecType::GetTime() const
{
    return m_time;
}

// Get speed
double WindRecType::GetSpeed() const
{
    return m_speed;
}
