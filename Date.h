#ifndef DATE_H
#define DATE_H

#include <iostream>

using std::ostream;
using std::istream;

/**
 * @class Date
 * @brief Represents a calendar date.
 *
 * Stores: Day, Month, Year
 *
 * @author Vernice Foong
 * @version 01
 */

class Date
{
public:

    /**
     * @brief Default constructor.
     */
    Date();

    /**
     * @brief Parameterized constructor.
     * @param day Day of month.
     * @param month Month.
     * @param year Year.
     */
    Date(int day, int month, int year);

    /**
     * @brief Gets day.
     * @return Day.
     */
    int GetDay() const;

    /**
     * @brief Sets day.
     * @param day New day.
     */
    void SetDay(int day);

    /**
     * @brief Gets month.
     * @return Month.
     */
    int GetMonth() const;

    /**
     * @brief Sets month.
     * @param month New month.
     */
    void SetMonth(int month);

    /**
     * @brief Gets year.
     * @return Year.
     */
    int GetYear() const;

    /**
     * @brief Sets year.
     * @param year New year.
     */
    void SetYear(int year);

    bool operator<(const Date& other) const
    {
        if (m_year != other.m_year)
            return m_year < other.m_year;

        if (m_month != other.m_month)
            return m_month < other.m_month;

        return m_day < other.m_day;
    }

    bool operator==(const Date& other) const
    {
        return (m_year == other.m_year &&
                m_month == other.m_month &&
                m_day == other.m_day);
    }
private:
    int m_day;
    int m_month;
    int m_year;
};

ostream & operator<<(ostream & os, const Date & date);
istream & operator>>(istream & input, Date & date);

#endif
