#ifndef WEATHERREC_H
#define WEATHERREC_H
#include "Date.h"
#include "Time.h"
#include <ostream>

/**
 * @class WeatherRec
 * @brief Represents a single 10-min weather record.
 *
 * Stores: Date, Time, Wind Speed (m/s), SR, T, and optional sensor values.
 *
 * @author Vernice Foong
 * @version 02
 */
class WeatherRec
{
public:

    /**
     * @brief Default constructor.
     */
    WeatherRec();

    /**
     * @brief Parameterized constructor.
     * @param date Date of the record.
     * @param time Time of the record.
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
    void SetDate(const Date& date);

    /**
     * @brief Gets the time.
     * @return Time of the record.
     */
    Time GetTime() const;

    /**
     * @brief Sets the time.
     * @param time New time.
     */
    void SetTime(const Time& time);

    /**
     * @brief Checks if wind speed value is valid.
     * @return True if wind speed exists.
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
     * @param valid True if value is valid.
     */
    void SetSpeed(double speed, bool valid);

    /**
     * @brief Checks if solar radiation value is valid.
     * @return True if solar radiation exists.
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
     * @param valid True if value is valid.
     */
    void SetSolarRadiation(double solar, bool valid);

    /**
     * @brief Checks if temperature value is valid.
     * @return True if temperature exists.
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
     * @param valid True if value is valid.
     */
    void SetTemperature(double temperature, bool valid);

    /**
     * @brief Compares two weather records by full timestamp.
     * @param other Another record.
     * @return True if this record is earlier than other.
     */
    bool operator<(const WeatherRec& other) const;

    /**
     * @brief Checks whether two records have the same full timestamp.
     * @param other Another record.
     * @return True if timestamps match.
     */
    bool operator==(const WeatherRec& other) const;

    /**
     * @brief Compares two weather records by full timestamp.
     * @param other Another record.
     * @return True if this record is later than other.
     */
    bool operator>(const WeatherRec& other) const;

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

/**
 * @brief Outputs a WeatherRec to a stream.
 * @param os Output stream.
 * @param rec Weather record.
 * @return Output stream.
 */
std::ostream& operator<<(std::ostream& os, const WeatherRec& rec);

#endif
