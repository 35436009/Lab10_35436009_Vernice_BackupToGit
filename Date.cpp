#include "Date.h"

// Default constructor
Date::Date()
{
    m_day = 1;
    m_month = 1;
    m_year = 1900;
}

// Parameterized constructor
Date::Date(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;

    SetDate(day, month, year);
}

// Get Day
int Date::GetDay() const
{
    return m_day;
}

// Set Day
void Date::SetDay(int day)
{
    if (IsValidDate(day, m_month, m_year))
    {
        m_day = day;
    }
}

// Get Month
int Date::GetMonth() const
{
    return m_month;
}

// Set Month
void Date::SetMonth(int month)
{
    if (IsValidDate(m_day, month, m_year))
    {
        m_month = month;
    }
}

// Get Year
int Date::GetYear() const
{
    return m_year;
}

// Set Year
void Date::SetYear(int year)
{
    if (IsValidDate(m_day, m_month, year))
    {
        m_year = year;
    }
}

// Validate date
bool Date::IsValid() const
{
    return IsValidDate(m_day, m_month, m_year);
}

bool Date::SetDate(int day, int month, int year)
{
    if (!IsValidDate(day, month, year))
    {
        return false;
    }

    m_day = day;
    m_month = month;
    m_year = year;
    return true;
}

// Check Leap Year
bool Date::IsLeapYear(int year)
{
    if (year % 400 == 0)
    {
        return true;
    }

    if (year % 100 == 0)
    {
        return false;
    }

    return year % 4 == 0;
}

bool Date::IsValidDate(int day, int month, int year)
{
    if (year <= 0 || month < 1 || month > 12 || day < 1)
    {
        return false;
    }

    int daysInMonth;

    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        daysInMonth = 31;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        daysInMonth = 30;
        break;

    case 2:
        if (IsLeapYear(year))
        {
            daysInMonth = 29;
        }
        else
        {
            daysInMonth = 28;
        }
        break;

    default:
        return false;
    }

    return day <= daysInMonth;
}

bool Date::operator==(const Date& other) const
{
    return m_year == other.m_year &&
           m_month == other.m_month &&
           m_day == other.m_day;
}


bool Date::operator<(const Date& other) const
{
    if (m_year != other.m_year)
    {
        return m_year < other.m_year;
    }

    if (m_month != other.m_month)
    {
        return m_month < other.m_month;
    }

    return m_day < other.m_day;
}

bool Date::operator>(const Date& other) const
{
    return other < *this;
}

// Output operator
ostream & operator<<(ostream & os, const Date & date)
{
    os << date.GetDay() << "/"
       << date.GetMonth() << "/"
       << date.GetYear();

    return os;
}

// Input operator
istream & operator>>(istream & input, Date & date)
{
    int day, month, year;
    char slash1, slash2;

    input >> day >> slash1 >> month >> slash2 >> year;

    if (!input || slash1 != '/' || slash2 != '/')
    {
        input.setstate(std::ios::failbit);
        return input;
    }

    if (!date.SetDate(day, month, year))
    {
        input.setstate(std::ios::failbit);
    }

    return input;
}
