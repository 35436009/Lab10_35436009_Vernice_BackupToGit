#ifndef TIME_H
#define TIME_H

#include <iostream>

using std::ostream;
using std::istream;

/**
 * @class Time
 * @brief Represents a time of day.
 *
 * Stores: Hour, Minute
 *
 * @author Vernice Foong
 * @version 01
 */

class Time
{
public:

    /**
     * @brief Default constructor.
     */
    Time();

    /**
     * @brief Parameterized constructor.
     * @param hour Hour.
     * @param minute Minute.
     */
    Time(int hour, int minute);

    /**
     * @brief Gets hour.
     * @return Hour.
     */
    int GetHour() const;

    /**
     * @brief Sets hour.
     * @param hour New hour.
     */
    void SetHour(int hour);

    /**
     * @brief Gets minute.
     * @return Minute.
     */
    int GetMinute() const;

    /**
     * @brief Sets minute.
     * @param minute New minute.
     */
    void SetMinute(int minute);

private:
    int m_hour;
    int m_minute;
};

ostream & operator<<(ostream & os, const Time & time);
istream & operator>>(istream & input, Time & time);

#endif
