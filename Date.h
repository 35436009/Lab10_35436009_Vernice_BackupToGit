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
 * @version 04
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

    /**
     * @brief Checks whether the stored date is valid.
     * @return True if valid, otherwise false.
     */
    bool IsValid() const;

    /**
     * @brief Sets the full date at once.
     * @param day Day of month.
     * @param month Month.
     * @param year Year.
     * @return True if the date is valid and was set.
     */
    bool SetDate(int day, int month, int year);

    /**
     * @brief Checks whether a year is a leap year.
     * @param year Year to check.
     * @return True if leap year, otherwise false.
     */
    static bool IsLeapYear(int year);

    /**
     * @brief Checks whether a date is valid.
     * @param day Day of month.
     * @param month Month.
     * @param year Year.
     * @return True if the date is valid, otherwise false.
     */
    static bool IsValidDate(int day, int month, int year);

    /**
     * @brief Equality operator.
     * @param other Another date.
     * @return True if both dates are equal.
     */
    bool operator==(const Date& other) const;

    /**
     * @brief Less-than operator.
     * @param other Another date.
     * @return True if this date is earlier than other.
     */
    bool operator<(const Date& other) const;

    /**
     * @brief Greater-than operator.
     * @param other Another date.
     * @return True if this date is later than other.
     */
    bool operator>(const Date& other) const;

private:
    int m_day;
    int m_month;
    int m_year;
};

ostream & operator<<(ostream & os, const Date & date);
istream & operator>>(istream & input, Date & date);

#endif