#ifndef WEATHERREC_H
#define WEATHERREC_H

#include "Date.h"
#include "Time.h"
#include <ostream>

/**
 * @class WeatherRec
 * @brief Represents one raw weather observation record.
 *
 * This class stores the timestamp and raw weather values loaded from the CSV.
 * It does not perform file loading or statistical processing.
 *
 * @author Vernice Foong
 * @version 03
 */
class WeatherRec
{
public:
    /**
     * @brief Default constructor.
     */
    WeatherRec();

    /**
     * @brief Constructs a record with a date and time.
     * @param date Date of the record.
     * @param time Time of the record.
     */
    WeatherRec(const Date& date, const Time& time);

    /**
     * @brief Gets the date.
     * @return The record date.
     */
    const Date& GetDate() const;

    /**
     * @brief Sets the date.
     * @param date New date value.
     */
    void SetDate(const Date& date);

    /**
     * @brief Gets the time.
     * @return The record time.
     */
    const Time& GetTime() const;

    /**
     * @brief Sets the time.
     * @param time New time value.
     */
    void SetTime(const Time& time);

    /**
     * @brief Checks whether wind speed is available.
     * @return True if wind speed exists, otherwise false.
     */
    bool HasSpeed() const;

    /**
     * @brief Gets the wind speed.
     * @return Wind speed in m/s.
     */
    double GetSpeed() const;

    /**
     * @brief Sets the wind speed.
     * @param speed Wind speed in m/s.
     * @param valid True if the value is valid.
     */
    void SetSpeed(double speed, bool valid);

    /**
     * @brief Checks whether solar radiation is available.
     * @return True if solar radiation exists, otherwise false.
     */
    bool HasSolar() const;

    /**
     * @brief Gets the solar radiation.
     * @return Solar radiation value.
     */
    double GetSolarRadiation() const;

    /**
     * @brief Sets the solar radiation.
     * @param solar Solar radiation value.
     * @param valid True if the value is valid.
     */
    void SetSolarRadiation(double solar, bool valid);

    /**
     * @brief Checks whether temperature is available.
     * @return True if temperature exists, otherwise false.
     */
    bool HasTemp() const;

    /**
     * @brief Gets the temperature.
     * @return Temperature value.
     */
    double GetTemperature() const;

    /**
     * @brief Sets the temperature.
     * @param temperature Temperature value.
     * @param valid True if the value is valid.
     */
    void SetTemperature(double temperature, bool valid);

    /**
     * @brief Compares two weather records by timestamp.
     * @param other Another record.
     * @return True if this record is earlier than other.
     */
    bool operator<(const WeatherRec& other) const;

    /**
     * @brief Checks whether two records have the same timestamp.
     * @param other Another record.
     * @return True if timestamps match.
     */
    bool operator==(const WeatherRec& other) const;

    /**
     * @brief Compares two weather records by timestamp.
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
 * @brief Outputs a weather record to a stream.
 * @param os Output stream.
 * @param rec Weather record.
 * @return Output stream.
 */
std::ostream& operator<<(std::ostream& os, const WeatherRec& rec);

#endif
