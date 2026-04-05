#include "UtilityStats.h"
#include <cmath>

// Helpers
static bool g_found = false;
// Wind
static double g_sum = 0;
static int g_count = 0;
static double g_varSum = 0;
static double g_mean = 0;

void VisitCheck(const WeatherRec& rec)
{
    if (rec.HasSpeed() || rec.HasTemp() ||
        (rec.HasSolar() && rec.GetSolarRadiation() >= 100.0))
    {
        g_found = true;
    }
}

void VisitWind(const WeatherRec& rec)
{
    if (rec.HasSpeed())
    {
        g_sum += rec.GetSpeed() * 3.6; // convert m/s to km/h
        g_count++;
    }
}

void VisitWindVar(const WeatherRec& rec)
{
    if (rec.HasSpeed())
    {
        double val = rec.GetSpeed() * 3.6;
        double diff = val - g_mean;
        g_varSum += diff * diff;
    }
}

// Temperature
void VisitTemp(const WeatherRec& rec)
{
    if (rec.HasTemp())
    {
        g_sum += rec.GetTemperature();
        g_count++;
    }
}

void VisitTempVar(const WeatherRec& rec)
{
    if (rec.HasTemp())
    {
        double diff = rec.GetTemperature() - g_mean;
        g_varSum += diff * diff;
    }
}

// Solar
static double g_solar = 0;

void VisitSolar(const WeatherRec& rec)
{
    if (rec.HasSolar() && rec.GetSolarRadiation() >= 100.0)
    {
        g_solar += rec.GetSolarRadiation() / 6000.0;
    }
}

// Mean Wind Speed (km/h)
double UtilityStats::MeanWind(
    const std::map<int, std::map<int, BST<WeatherRec> > > & dataMap,
    int year, int month)
{
    auto itYear = dataMap.find(year);
    if (itYear == dataMap.end()) return 0.0;

    auto itMonth = itYear->second.find(month);
    if (itMonth == itYear->second.end()) return 0.0;

    g_sum = 0;
    g_count = 0;

    itMonth->second.Inorder(VisitWind);

    if (g_count == 0) return 0.0;
    return g_sum / g_count;
}

// Standard Deviation Wind
double UtilityStats::SDWind(
    const std::map<int, std::map<int, BST<WeatherRec> > > & dataMap,
    int year, int month, double mean)
{
    auto itYear = dataMap.find(year);
    if (itYear == dataMap.end()) return 0.0;

    auto itMonth = itYear->second.find(month);
    if (itMonth == itYear->second.end()) return 0.0;

    g_mean = mean;
    g_varSum = 0;
    g_count = 0;

    // Count valid records
    itMonth->second.Inorder(VisitWind);

    if (g_count <= 1) return 0.0;

    // Compute variance
    g_varSum = 0;
    itMonth->second.Inorder(VisitWindVar);

    return std::sqrt(g_varSum / (g_count - 1));
}

// Mean Temperature
double UtilityStats::MeanTemp(
    const std::map<int, std::map<int, BST<WeatherRec> > > & dataMap,
    int year, int month)
{
    auto itYear = dataMap.find(year);
    if (itYear == dataMap.end()) return 0.0;

    auto itMonth = itYear->second.find(month);
    if (itMonth == itYear->second.end()) return 0.0;

    g_sum = 0;
    g_count = 0;

    itMonth->second.Inorder(VisitTemp);

    if (g_count == 0) return 0.0;
    return g_sum / g_count;
}

// Standard Deviation Temperature
double UtilityStats::SDTemp(
    const std::map<int, std::map<int, BST<WeatherRec> > > & dataMap,
    int year, int month, double mean)
{
    auto itYear = dataMap.find(year);
    if (itYear == dataMap.end()) return 0.0;

    auto itMonth = itYear->second.find(month);
    if (itMonth == itYear->second.end()) return 0.0;

    g_mean = mean;
    g_varSum = 0;
    g_count = 0;

    itMonth->second.Inorder(VisitTemp);

    if (g_count <= 1) return 0.0;

    g_varSum = 0;
    itMonth->second.Inorder(VisitTempVar);

    return std::sqrt(g_varSum / (g_count - 1));
}

// Solar Total (kWh/m^2)
double UtilityStats::SolarTotal(
    const std::map<int, std::map<int, BST<WeatherRec> > > & dataMap,
    int year, int month)
{
    auto itYear = dataMap.find(year);
    if (itYear == dataMap.end()) return 0.0;

    auto itMonth = itYear->second.find(month);
    if (itMonth == itYear->second.end()) return 0.0;

    g_solar = 0;

    itMonth->second.Inorder(VisitSolar);

    return g_solar;
}

// Check if any data exists
bool UtilityStats::HasAnyDataForMonth(
    const std::map<int, std::map<int, BST<WeatherRec> > > & dataMap,
    int year, int month)
{
    auto itYear = dataMap.find(year);
    if (itYear == dataMap.end()) return false;

    auto itMonth = itYear->second.find(month);
    if (itMonth == itYear->second.end()) return false;

    g_found = false;

    itMonth->second.Inorder(VisitCheck);

    return g_found;
}



