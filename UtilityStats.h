#ifndef UTILITYSTATS_H
#define UTILITYSTATS_H

#include "Vector.h"
#include "MonthlySummary.h"

/**
 * @class UtilityStats
 * @brief Provides statistical calculations for weather data.
 *
 * This class contains only static helper functions for computations.
 * It does not load files or store records.
 *
 * @author Vernice Foong
 * @version 04
 */
class UtilityStats
{
public:
    /**
     * @brief Computes the mean of a vector of floating-point values.
     * @param values Vector of values.
     * @return Mean value, or 0.0 if the vector is empty.
     */
    static float Mean(const Vector<float>& values);

    /**
     * @brief Computes the sample standard deviation of a vector of floating-point values.
     * @param values Vector of values.
     * @param mean Precomputed mean value.
     * @return Sample standard deviation, or 0.0 if not enough values.
     */
    static float StDev(const Vector<float>& values, float mean);

    /**
     * @brief Computes the mean absolute deviation of a vector of floating-point values.
     * @param values Vector of values.
     * @param mean Precomputed mean value.
     * @return Mean absolute deviation, or 0.0 if the vector is empty.
     */
    static float Mad(const Vector<float>& values, float mean);

    /**
     * @brief Computes the sample Pearson correlation coefficient.
     * @param xValues First data series.
     * @param yValues Second data series.
     * @param result Output correlation result.
     * @return True if the calculation succeeds, otherwise false.
     */
    static bool ComputeSPCC(const Vector<double>& xValues,
                            const Vector<double>& yValues,
                            double& result);

    /**
     * @brief Builds a monthly summary object.
     * @param year Year of the summary.
     * @param month Month of the summary.
     * @param meanSpeed Mean wind speed.
     * @param speedStDev Wind speed standard deviation.
     * @param speedMad Wind speed mean absolute deviation.
     * @param meanTemp Mean temperature.
     * @param tempStDev Temperature standard deviation.
     * @param tempMad Temperature mean absolute deviation.
     * @param solarTotal Total solar radiation.
     * @param spccST SPCC for speed and temperature.
     * @param spccSR SPCC for speed and solar radiation.
     * @param spccTR SPCC for temperature and solar radiation.
     * @param hasData True if the month has usable data.
     * @return Filled MonthlySummary object.
     */
    static MonthlySummary BuildMonthlySummary(int year,
                                              int month,
                                              float meanSpeed,
                                              float speedStDev,
                                              float speedMad,
                                              float meanTemp,
                                              float tempStDev,
                                              float tempMad,
                                              double solarTotal,
                                              double spccST,
                                              double spccSR,
                                              double spccTR,
                                              bool hasData);
};

#endif
