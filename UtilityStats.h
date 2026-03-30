#ifndef UTILITYSTATS_H_INCLUDED
#define UTILITYSTATS_H_INCLUDED

#include "Vector.h"
#include "WeatherLog.h"

/**
 * @class UtilityStats
 * @brief Utility class for performing statistical calculations.
 *
 * This class contains only static methods.
 *
 * Responsibilities:
 * - Compute mean and sample SD
 * - Compute mean absolute deviation
 * - Compute monthly solar total
 * - Check if any data exists for a month
 *
 * Rules:
 * - Statistical routines operate on Vector<float>, not on weather types.
 * - Wind speed values should be converted to km/h before being passed in.
 * - Solar radiation: only include values >= 100 W/m^2, convert each 10-minute reading to kWh/m^2
 *   using SR / 6000 and sum per month.
 *
 * @author Vernice Foong
 * @version 05
 */
class UtilityStats
{
public:
    /**
     * @brief Computes the mean of a vector of floating-point values.
     *
     * @param values The vector of values to average.
     * @return The arithmetic mean of the values, or 0.0f if the vector is empty.
     */
    static float Mean(const Vector<float>& values);

    /**
     * @brief Computes the sample standard deviation of a vector of floating-point values.
     *
     * Uses the sample standard deviation formula with denominator (n - 1).
     *
     * @param values The vector of values to process.
     * @param mean   The precomputed mean of the values.
     * @return The sample standard deviation, or 0.0f if the vector has fewer than 2 values.
     */
    static float StDev(const Vector<float>& values, float mean);

    /**
     * @brief Computes the mean absolute deviation of a vector of floating-point values.
     *
     * The mean absolute deviation is the average of the absolute differences
     * from the mean.
     *
     * @param values The vector of values to process.
     * @param mean   The precomputed mean of the values.
     * @return The mean absolute deviation, or 0.0f if the vector is empty.
     */
    static float Mad(const Vector<float>& values, float mean);

    /**
     * @brief Computes the total solar radiation for a specified month and year.
     *
     * Only solar radiation values >= 100 W/m^2 are included.
     * Each 10-minute reading is converted to kWh/m^2 using:
     *      kWh/m^2 = SR / 6000 and summed for the month.
     *
     * @param log   Reference to WeatherLog containing all records.
     * @param year  The year to filter.
     * @param month The month to filter (1~12).
     * @return The total solar radiation in kWh/m^2.
     */
    static double SolarTotal(const WeatherLog& log, int year, int month);

    /**
     * @brief Checks whether any usable data exists for a given month and year.
     *
     * A month is considered to have data if:
     * - It contains at least one valid wind reading, OR
     * - It contains at least one valid temperature reading, OR
     * - It contains at least one usable solar reading (>= 100 W/m^2).
     *
     * Used primarily for determining whether a month should be written
     * in the CSV output for menu option 4.
     *
     * @param log   Reference to WeatherLog containing all records.
     * @param year  The year to filter.
     * @param month The month to filter (1~12).
     * @return true if the month contains usable data; false otherwise.
     */
    static bool HasAnyDataForMonth(const WeatherLog& log, int year, int month);
};

#endif
