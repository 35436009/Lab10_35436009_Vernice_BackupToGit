#include "UtilityStats.h"
#include <cmath>

// Returns true if the record belongs to the given month and year.
static bool MatchMonthYear(const WeatherRec& rec, int year, int month)
{
    return rec.GetDate().GetYear() == year &&
           rec.GetDate().GetMonth() == month;
}

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

// Computes the total solar radiation for a specified month and year.
double UtilityStats::SolarTotal(const WeatherLog& log, int year, int month)
{
    double total = 0.0;

    for (int i = 0; i < log.GetSize(); i++)
    {
        const WeatherRec& rec = log.GetRecord(i);

        if (MatchMonthYear(rec, year, month) &&
            rec.HasSolar() &&
            rec.GetSolarRadiation() >= 100.0)
        {
            total += rec.GetSolarRadiation() / 6000.0;
        }
    }

    return total;
}

// Checks whether any usable data exists for a given month and year.
bool UtilityStats::HasAnyDataForMonth(const WeatherLog& log, int year, int month)
{
    for (int i = 0; i < log.GetSize(); i++)
    {
        const WeatherRec& rec = log.GetRecord(i);

        if (MatchMonthYear(rec, year, month))
        {
            if (rec.HasSpeed() || rec.HasTemp())
            {
                return true;
            }

            if (rec.HasSolar() && rec.GetSolarRadiation() >= 100.0)
            {
                return true;
            }
        }
    }

    return false;
}