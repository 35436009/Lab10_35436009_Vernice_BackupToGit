#ifndef WEATHERREC_H
#define WEATHERREC_H
#include "Date.h"
#include "Time.h"

/**
 * @class WeatherRec
 * @brief Represents a single 10-min weather record.
 *
 * Stores:Date, Time, Wind Speed (m/s), SR, T, and optional sensor values.
 *
 * @author Vernice Foong
 * @version 01
 */

class WeatherRec
{
public:

    /**
     * @brief Default constructor
     */
    WeatherRec();

    /**
     * @brief Parameterized constructor
     */
    WeatherRec(const Date& date, const Time& time);


    /**
     * @brief Gets the date.
     * @return Date of the record.
     */
    Date GetDate() const;

    /**
     * @brief Sets the date.
     * @param date New date.
     */
    void SetDate(const Date & date);

    /**
     * @brief Gets the time.
     * @return Time of the record.
     */
    Time GetTime() const;

    /**
     * @brief Sets the time.
     * @param time New time.
     */
    void SetTime(const Time & time);

    /**
     * @brief Checks if wind speed value is valid.
     * @return true if wind speed exists.
     */
    bool HasSpeed() const;

    /**
     * @brief Gets wind speed.
     * @return Wind speed in m/s.
     */
    double GetSpeed() const;

    /**
     * @brief Sets wind speed.
     * @param speed Wind speed in m/s.
     */
    void SetSpeed(double speed, bool valid);

    /**
     * @brief Checks if solar radiation value is valid.
     * @return true if solar radiation exists.
     */
    bool HasSolar() const;

    /**
     * @brief Gets solar radiation.
     * @return Solar radiation value.
     */
    double GetSolarRadiation() const;

    /**
     * @brief Sets solar radiation.
     * @param solar Solar radiation value.
     */
    void SetSolarRadiation(double solar, bool valid);

    /**
     * @brief Checks if temperature value is valid.
     * @return true if temperature exists.
     */
     bool HasTemp() const;

    /**
     * @brief Gets temperature.
     * @return Ambient air temperature.
     */
    double GetTemperature() const;

    /**
     * @brief Sets temperature.
     * @param temperature Ambient air temperature.
     */
    void SetTemperature(double temperature, bool valid);

bool operator<(const WeatherRec& other) const
{
    if (m_date.GetYear() != other.m_date.GetYear())
        return m_date.GetYear() < other.m_date.GetYear();

    if (m_date.GetMonth() != other.m_date.GetMonth())
        return m_date.GetMonth() < other.m_date.GetMonth();

    return m_date.GetDay() < other.m_date.GetDay();
}

bool operator==(const WeatherRec& other) const
{
    return m_date.GetYear() == other.m_date.GetYear() &&
           m_date.GetMonth() == other.m_date.GetMonth() &&
           m_date.GetDay() == other.m_date.GetDay();
}

bool operator>(const WeatherRec& other) const
{
    if (m_date.GetYear() != other.m_date.GetYear())
        return m_date.GetYear() > other.m_date.GetYear();

    if (m_date.GetMonth() != other.m_date.GetMonth())
        return m_date.GetMonth() > other.m_date.GetMonth();

    return m_date.GetDay() > other.m_date.GetDay();
}

private:
    Date m_date;
    Time m_time;

    double m_speed;
    double m_solarRadiation;
    double m_temperature;

    bool m_hasSpeed;
    bool m_hasSolar;
    bool m_hasTemp;
};

// Stream output so WeatherRec can be printed in TestVector
std::ostream& operator<<(std::ostream& os, const WeatherRec& rec);

#endif
