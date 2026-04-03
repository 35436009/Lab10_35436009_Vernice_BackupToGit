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
}

// Get Day
int Date::GetDay() const
{
    return m_day;
}

// Set Day
void Date::SetDay(int day)
{
    m_day = day;
}

// Get Month
int Date::GetMonth() const
{
    return m_month;
}

// Set Month
void Date::SetMonth(int month)
{
    m_month = month;
}

// Get Year
int Date::GetYear() const
{
    return m_year;
}

// Set Year
void Date::SetYear(int year)
{
    m_year = year;
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

    date.SetDay(day);
    date.SetMonth(month);
    date.SetYear(year);

    return input;
}
