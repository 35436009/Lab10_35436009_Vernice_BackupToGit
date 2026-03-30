#ifndef WINDRECTYPE_H
#define WINDRECTYPE_H

#include "Date.h"
#include "Time.h"

/**
 * @brief Represents a single wind data record.
 * Stores date, time, and wind speed (in m/s).
 *
 * @author Vernice Foong
 * @version 01
 */
class WindRecType
{
public:
    /**
     * @brief Default constructor
     */
    WindRecType();

    /**
     * @brief Parameterised constructor
     */
    WindRecType(const Date& date, const Time& time, double speed);

    /**
     * @brief Sets date
     */
    void SetDate(const Date& date);

    /**
     * @brief Sets time
     */
    void SetTime(const Time& time);

    /**
     * @brief Sets wind speed (m/s)
     */
    void SetSpeed(double speed);

    /**
     * @brief Returns date
     */
    Date GetDate() const;

    /**
     * @brief Returns time
     */
    Time GetTime() const;

    /**
     * @brief Returns wind speed (m/s)
     */
    double GetSpeed() const;

private:
    Date m_date;
    Time m_time;
    double m_speed;   // stored in m/s
};

#endif
