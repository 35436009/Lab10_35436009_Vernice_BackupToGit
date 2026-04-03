#ifndef UTILITYSTATS_H_INCLUDED
#define UTILITYSTATS_H_INCLUDED

#include "WeatherLog.h"

/**
 * @class UtilityStats
 * @brief Utility class for performing statistical calculations.
 *
 * This class contains only static methods.
 *
 * Responsibilities:
 * - Compute wind mean and sample SD
 * - Compute temperature mean and sample SD
 * - Compute monthly solar total
 * - Check if any data exists for a month
* Rules:
 * - Wind speed: output in km/h (input stored in m/s)
 * - Solar radiation: only include values >= 100 W/m^2, convert each 10-min reading to kWh/m^2
 *   using SR / 6000 and sum per month
 *
 * @author Vernice Foong
 * @version 03
 */
class UtilityStats
{
public:

    /**
     * @brief Computes the mean wind speed (km/h) for a specified month and year.
     *
     * Wind speed values are stored internally in m/s.
     * This function converts them to km/h before calculating the average.
     * Only valid wind readings are included.
     *
     * @param log   Reference to WeatherLog containing all records.
     * @param year  The year to filter.
     * @param month The month to filter (1~12).
     * @return The mean wind speed in km/h.
     */
    static double MeanWind(const WeatherLog& log, int year, int month);

    /**
     *@brief Computes the sample standard deviation of wind speed (km/h).
     *
     * Uses the sample standard deviation formula (n - 1).
     * Wind values are converted from m/s to km/h before computation.
     * Only valid wind readings are included.
     *
     * @param log   Reference to WeatherLog containing all records.
     * @param year  The year to filter.
     * @param month The month to filter (1~12).
     * @param mean  Precomputed mean wind speed (km/h).
     * @return The sample standard deviation of wind speed.
     */
    static double SDWind(const WeatherLog& log, int year, int month, double mean);

    /**
     * @brief Computes the mean temperature (degrees C) for a specified month and year.
     *
     * Only valid temperature readings are included.
     * No unit conversion is performed.
     *
     * @param log   Reference to WeatherLog containing all records.
     * @param year  The year to filter.
     * @param month The month to filter (1~12).
     * @return The mean temperature in degrees Celsius.
     */
    static double MeanTemp(const WeatherLog& log, int year, int month);

    /**
     * @brief Computes the sample standard deviation of temperature.
     *
     * Uses the sample standard deviation formula (n - 1).
     * Only valid temperature readings are included.
     *
     * @param log   Reference to WeatherLog containing all records.
     * @param year  The year to filter.
     * @param month The month to filter (1 to 12).
     * @param mean  Precomputed mean temperature.
     * @return The sample standard deviation of temperature.
     */
    static double SDTemp(const WeatherLog& log, int year, int month, double mean);

    /**
     * @brief Computes the total solar radiation for a specified month and year.
     *
     * Only solar radiation values >= 100 W/m^2 are included.
     * Each 10-minute reading is converted to kWh/m^2 using:
     *      kWh/m^2 = SR / 6000
     * and summed for the month.
     *
     * @param log   Reference to WeatherLog containing all records.
     * @param year  The year to filter.
     * @param month The month to filter (1 to 12).
     * @return The total solar radiation in kWh/m^2.
     */
    static double SolarTotal(const WeatherLog& log, int year, int month);

    /**
     * @brief Checks whether any usable data exists for a given month and year.
     *
     * A month is considered to have data if:
     * It contains at least one valid wind reading, OR
     * at least one valid temperature reading, OR
     * at least one usable solar reading (>= 100 W/m^2).
     *
     * Used primarily for determining whether a month should be written
     * in the CSV output for menu option 4.
     *
     * @param log   Reference to WeatherLog containing all records.
     * @param year  The year to filter.
     * @param month The month to filter (1 to 12).
     * @return true if the month contains usable data; false otherwise.
     */
    static bool HasAnyDataForMonth(const WeatherLog& log, int year, int month);
};

#endif
