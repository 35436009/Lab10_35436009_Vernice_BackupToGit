#ifndef UTILITYSTATS_H_INCLUDED
#define UTILITYSTATS_H_INCLUDED

#include <map>
#include "BST.h"
#include "WeatherRec.h"

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
     * @param month The month to filter (1 to 12).
     * @return The mean wind speed in km/h.
     */
static double MeanWind(
    const std::map<int, std::map<int, BST<WeatherRec> > > & dataMap,
    int year, int month);

static double SDWind(
    const std::map<int, std::map<int, BST<WeatherRec> > > & dataMap,
    int year, int month, double mean);

static double MeanTemp(
    const std::map<int, std::map<int, BST<WeatherRec> > > & dataMap,
    int year, int month);

static double SDTemp(
    const std::map<int, std::map<int, BST<WeatherRec> > > & dataMap,
    int year, int month, double mean);

static double SolarTotal(
    const std::map<int, std::map<int, BST<WeatherRec> > > & dataMap,
    int year, int month);

static bool HasAnyDataForMonth(
    const std::map<int, std::map<int, BST<WeatherRec> > > & dataMap,
    int year, int month);
};

#endif
