#include "UtilityStats.h"
#include <cmath>

// Private helpers

// Checks whether a record belongs to the given month and year.
static bool MatchMonthYear(const WeatherRec& rec, int year, int month)
{
    return rec.GetDate().GetYear() == year &&
           rec.GetDate().GetMonth() == month;
}

// Checks whether the month has any usable solar value.
static bool HasUsableSolarForMonth(const WeatherLog& log, int year, int month)
{
    for (int i = 0; i < log.GetSize(); i++)
    {
        const WeatherRec& rec = log.GetRecord(i);

        if (MatchMonthYear(rec, year, month) && rec.HasSolar())
        {
            if (rec.GetSolarRadiation() >= 100.0)
            {
                return true;
            }
        }
    }

    return false;
}

// Computes the mean wind speed in km/h.
double UtilityStats::MeanWind(const WeatherLog& log, int year, int month)
{
    double sum = 0.0;
    int count = 0;

    for (int i = 0; i < log.GetSize(); i++)
    {
        const WeatherRec& rec = log.GetRecord(i);

        if (MatchMonthYear(rec, year, month) && rec.HasSpeed())
        {
            double speedKmh = rec.GetSpeed() * 3.6;
            sum += speedKmh;
            count++;
        }
    }

    if (count == 0)
    {
        return 0.0;
    }
    else
    {
        return sum / count;
    }
}

// Computes the sample standard deviation of wind speed in km/h.
double UtilityStats::SDWind(const WeatherLog& log, int year, int month, double mean)
{
    double sumSquares = 0.0;
    int count = 0;

    for (int i = 0; i < log.GetSize(); i++)
    {
        const WeatherRec& rec = log.GetRecord(i);

        if (MatchMonthYear(rec, year, month) && rec.HasSpeed())
        {
            double speedKmh = rec.GetSpeed() * 3.6;
            double diff = speedKmh - mean;
            sumSquares += diff * diff;
            count++;
        }
    }

    if (count <= 1)
    {
        return 0.0;
    }
    else
    {
        return std::sqrt(sumSquares / (count - 1));
    }
}

// Computes the mean temperature in degrees C.
double UtilityStats::MeanTemp(const WeatherLog& log, int year, int month)
{
    double sum = 0.0;
    int count = 0;

    for (int i = 0; i < log.GetSize(); i++)
    {
        const WeatherRec& rec = log.GetRecord(i);

        if (MatchMonthYear(rec, year, month) && rec.HasTemp())
        {
            sum += rec.GetTemperature();
            count++;
        }
    }

    if (count == 0)
    {
        return 0.0;
    }
    else
    {
        return sum / count;
    }
}

// Computes the sample standard deviation of temperature.
double UtilityStats::SDTemp(const WeatherLog& log, int year, int month, double mean)
{
    double sumSquares = 0.0;
    int count = 0;

    for (int i = 0; i < log.GetSize(); i++)
    {
        const WeatherRec& rec = log.GetRecord(i);

        if (MatchMonthYear(rec, year, month) && rec.HasTemp())
        {
            double diff = rec.GetTemperature() - mean;
            sumSquares += diff * diff;
            count++;
        }
    }

    if (count <= 1)
    {
        return 0.0;
    }
    else
    {
        return std::sqrt(sumSquares / (count - 1));
    }
}

// Computes the monthly total solar radiation in kWh/m^2.
double UtilityStats::SolarTotal(const WeatherLog& log, int year, int month)
{
    double total = 0.0;
    bool foundUsable = false;

    for (int i = 0; i < log.GetSize(); i++)
    {
        const WeatherRec& rec = log.GetRecord(i);

        if (MatchMonthYear(rec, year, month) && rec.HasSolar())
        {
            double solar = rec.GetSolarRadiation();

            if (solar >= 100.0)
            {
                total += (solar / 6000.0);
                foundUsable = true;
            }
        }
    }

    if (foundUsable)
    {
        return total;
    }
    else
    {
        return 0.0;
    }
}

// Checks whether the month has any usable wind, temperature, or solar data.
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
        }
    }

    if (HasUsableSolarForMonth(log, year, month))
    {
        return true;
    }
    else
    {
        return false;
    }
}