#include "UtilityStats.h"
#include <cmath>

// Computes the mean of a vector of floating-point values.
float UtilityStats::Mean(const Vector<float>& values)
{
    if (values.GetSize() == 0)
    {
        return 0.0f;
    }

    float sum = 0.0f;

    for (int i = 0; i < values.GetSize(); i++)
    {
        sum += values[i];
    }

    return sum / values.GetSize();
}

// Computes the sample standard deviation of a vector of floating-point values.
float UtilityStats::StDev(const Vector<float>& values, float mean)
{
    if (values.GetSize() <= 1)
    {
        return 0.0f;
    }

    float sumSquares = 0.0f;

    for (int i = 0; i < values.GetSize(); i++)
    {
        float diff = values[i] - mean;
        sumSquares += diff * diff;
    }

    return std::sqrt(sumSquares / (values.GetSize() - 1));
}

// Computes the mean absolute deviation of a vector of floating-point values.
float UtilityStats::Mad(const Vector<float>& values, float mean)
{
    if (values.GetSize() == 0)
    {
        return 0.0f;
    }

    float sumAbs = 0.0f;

    for (int i = 0; i < values.GetSize(); i++)
    {
        sumAbs += std::fabs(values[i] - mean);
    }

    return sumAbs / values.GetSize();
}

// Computes the sample Pearson correlation coefficient.
bool UtilityStats::ComputeSPCC(const Vector<double>& xValues,
                               const Vector<double>& yValues,
                               double& result)
{
    if (xValues.GetSize() != yValues.GetSize())
    {
        return false;
    }
    else if (xValues.GetSize() <= 1)
    {
        return false;
    }

    double sumX = 0.0;
    double sumY = 0.0;
    double sumXY = 0.0;
    double sumX2 = 0.0;
    double sumY2 = 0.0;

    for (int i = 0; i < xValues.GetSize(); i++)
    {
        double x = xValues[i];
        double y = yValues[i];

        sumX += x;
        sumY += y;
        sumXY += x * y;
        sumX2 += x * x;
        sumY2 += y * y;
    }

    double numerator = xValues.GetSize() * sumXY - sumX * sumY;
    double denominator = std::sqrt((xValues.GetSize() * sumX2 - sumX * sumX) *
                                    (xValues.GetSize() * sumY2 - sumY * sumY));

    if (denominator == 0.0)
    {
        return false;
    }
    else
    {
        result = numerator / denominator;
        return true;
    }
}

// Builds a monthly summary object.
MonthlySummary UtilityStats::BuildMonthlySummary(int year,
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
                                                 bool hasData)
{
    MonthlySummary summary;

    summary.SetYear(year);
    summary.SetMonth(month);
    summary.SetMeanSpeed(meanSpeed);
    summary.SetSpeedStDev(speedStDev);
    summary.SetSpeedMad(speedMad);
    summary.SetMeanTemp(meanTemp);
    summary.SetTempStDev(tempStDev);
    summary.SetTempMad(tempMad);
    summary.SetSolarTotal(solarTotal);
    summary.SetSPCCSpeedTemp(spccST);
    summary.SetSPCCSpeedSolar(spccSR);
    summary.SetSPCCTempSolar(spccTR);
    summary.SetHasData(hasData);

    return summary;
}