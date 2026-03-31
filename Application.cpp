#include "Application.h"
#include "UtilityStats.h"
#include <iostream>
#include <fstream>
#include <cmath>

// Helpers for collecting filtered values from traversal callbacks.
// The BST callback interface uses a simple function pointer.
static int g_targetYear = 0;
static int g_targetMonth = 0;

static Vector<float>* g_windValues = NULL;
static Vector<float>* g_tempValues = NULL;

static double g_sumST_x = 0.0;
static double g_sumST_y = 0.0;
static double g_sumST_xy = 0.0;
static double g_sumST_x2 = 0.0;
static double g_sumST_y2 = 0.0;

static double g_sumSR_x = 0.0;
static double g_sumSR_y = 0.0;
static double g_sumSR_xy = 0.0;
static double g_sumSR_x2 = 0.0;
static double g_sumSR_y2 = 0.0;

static double g_sumTR_x = 0.0;
static double g_sumTR_y = 0.0;
static double g_sumTR_xy = 0.0;
static double g_sumTR_x2 = 0.0;
static double g_sumTR_y2 = 0.0;

static int g_nST = 0;
static int g_nSR = 0;
static int g_nTR = 0;

// Collects wind values for option 1.
static void CollectWindValues(const WeatherRec& rec)
{
    if (rec.GetDate().GetMonth() == g_targetMonth &&
        rec.HasSpeed() &&
        g_windValues != NULL)
    {
        g_windValues->Add(static_cast<float>(rec.GetSpeed() * 3.6));
    }
}

// Collects temperature values for option 2.
static void CollectTempValues(const WeatherRec& rec)
{
    if (rec.GetDate().GetMonth() >= 1 &&
        rec.GetDate().GetMonth() <= 12 &&
        rec.HasTemp() &&
        g_tempValues != NULL)
    {
        g_tempValues->Add(static_cast<float>(rec.GetTemperature()));
    }
}

// Collects wind, temperature, and solar data for option 3.
static void CollectSPCCValues(const WeatherRec& rec)
{
    if (rec.GetDate().GetMonth() != g_targetMonth)
    {
        return;
    }

    if (rec.HasSpeed() && rec.HasTemp())
    {
        double x = rec.GetSpeed();
        double y = rec.GetTemperature();
        g_sumST_x += x;
        g_sumST_y += y;
        g_sumST_xy += x * y;
        g_sumST_x2 += x * x;
        g_sumST_y2 += y * y;
        g_nST++;
    }

    if (rec.HasSpeed() && rec.HasSolar())
    {
        double x = rec.GetSpeed();
        double y = rec.GetSolarRadiation();
        g_sumSR_x += x;
        g_sumSR_y += y;
        g_sumSR_xy += x * y;
        g_sumSR_x2 += x * x;
        g_sumSR_y2 += y * y;
        g_nSR++;
    }

    if (rec.HasTemp() && rec.HasSolar())
    {
        double x = rec.GetTemperature();
        double y = rec.GetSolarRadiation();
        g_sumTR_x += x;
        g_sumTR_y += y;
        g_sumTR_xy += x * y;
        g_sumTR_x2 += x * x;
        g_sumTR_y2 += y * y;
        g_nTR++;
    }
}

// Collects wind and temperature values for option 4.
static void CollectWindTempValues(const WeatherRec& rec)
{
    if (rec.GetDate().GetYear() != g_targetYear ||
        rec.GetDate().GetMonth() != g_targetMonth)
    {
        return;
    }

    if (rec.HasSpeed() && g_windValues != NULL)
    {
        g_windValues->Add(static_cast<float>(rec.GetSpeed() * 3.6));
    }

    if (rec.HasTemp() && g_tempValues != NULL)
    {
        g_tempValues->Add(static_cast<float>(rec.GetTemperature()));
    }
}

// Constructor for reference to WeatherLog.
Application::Application(WeatherLog& log)
    : m_log(log)
{
}

// Runs the main menu loop.
void Application::Run()
{
    int choice = 0;

    do
    {
        DisplayMenu();
        choice = ReadInt();

        switch (choice)
        {
        case 1:
            DoOption1();
            break;
        case 2:
            DoOption2();
            break;
        case 3:
            DoOption3();
            break;
        case 4:
            DoOption4();
            break;
        case 5:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }
    while (choice != 5);
}

// Displays the menu options.
void Application::DisplayMenu() const
{
    std::cout << "1. Wind speed stats (month/year)\n";
    std::cout << "2. Temperature stats (year)\n";
    std::cout << "3. sPCC calculation (month)\n";
    std::cout << "4. Generate WindTempSolar.csv\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter choice: ";
}

// Reads an integer from the user.
int Application::ReadInt() const
{
    int value;
    std::cin >> value;
    return value;
}

// Returns the English month name.
const char* Application::GetMonthName(int month) const
{
    static const char* names[] =
    {
        "January","February","March","April","May","June",
        "July","August","September","October","November","December"
    };

    if (month >= 1 && month <= 12)
    {
        return names[month - 1];
    }

    return "";
}

// Rounds a value to 2 decimal places.
static double Round2(double value)
{
    return std::floor(value * 100.0 + 0.5) / 100.0;
}

// Computes sample Pearson correlation coefficient.
static bool ComputeSPCC(int n, double sumX, double sumY, double sumXY,
                        double sumX2, double sumY2, double& result)
{
    if (n < 2)
    {
        return false;
    }

    double numerator = n * sumXY - sumX * sumY;
    double denominator = std::sqrt((n * sumX2 - sumX * sumX) *
                                   (n * sumY2 - sumY * sumY));

    if (denominator == 0.0)
    {
        return false;
    }

    result = numerator / denominator;
    return true;
}

// Menu option 1 for wind stats.
void Application::DoOption1()
{
    std::cout << "Enter month (1-12): ";
    int month = ReadInt();

    std::cout << "Enter year: ";
    int year = ReadInt();

    if (month < 1 || month > 12)
    {
        std::cout << "Invalid month.\n";
        return;
    }

    Vector<float> windValues;
    g_targetMonth = month;
    g_windValues = &windValues;

    m_log.TraverseYear(year, CollectWindValues);

    g_windValues = NULL;

    if (windValues.GetSize() == 0)
    {
        std::cout << GetMonthName(month) << " " << year << ": No Data\n";
        return;
    }

    float mean = UtilityStats::Mean(windValues);
    float sd = UtilityStats::StDev(windValues, mean);
    float mad = UtilityStats::Mad(windValues, mean);

    std::cout << GetMonthName(month) << " " << year << ":\n";
    std::cout << "Average speed: " << Round2(mean) << " km/h\n";
    std::cout << "Sample stdev: " << Round2(sd) << "\n";
    std::cout << "Mean absolute deviation: " << Round2(mad) << "\n";
}

// Menu option 2 for temperature stats.
void Application::DoOption2()
{
    std::cout << "Enter year: ";
    int year = ReadInt();

    std::cout << year << "\n";

    for (int month = 1; month <= 12; month++)
    {
        Vector<float> tempValues;
        g_targetMonth = month;
        g_tempValues = &tempValues;

        m_log.TraverseYear(year, CollectTempValues);

        g_tempValues = NULL;

        if (tempValues.GetSize() == 0)
        {
            std::cout << GetMonthName(month) << ": No Data\n";
        }
        else
        {
            float mean = UtilityStats::Mean(tempValues);
            float sd = UtilityStats::StDev(tempValues, mean);

            std::cout << GetMonthName(month)
                      << ": average: " << Round2(mean)
                      << " degrees C, stdev: " << Round2(sd)
                      << "\n";
        }
    }
}

// Menu option 3: Sample Pearson Correlation Coefficient for a month.
void Application::DoOption3()
{
    std::cout << "Enter month (1-12): ";
    int month = ReadInt();

    if (month < 1 || month > 12)
    {
        std::cout << "Invalid month.\n";
        return;
    }

    g_targetMonth = month;

    g_sumST_x = 0.0;
    g_sumST_y = 0.0;
    g_sumST_xy = 0.0;
    g_sumST_x2 = 0.0;
    g_sumST_y2 = 0.0;

    g_sumSR_x = 0.0;
    g_sumSR_y = 0.0;
    g_sumSR_xy = 0.0;
    g_sumSR_x2 = 0.0;
    g_sumSR_y2 = 0.0;

    g_sumTR_x = 0.0;
    g_sumTR_y = 0.0;
    g_sumTR_xy = 0.0;
    g_sumTR_x2 = 0.0;
    g_sumTR_y2 = 0.0;

    g_nST = 0;
    g_nSR = 0;
    g_nTR = 0;

    m_log.TraverseAllYears(CollectSPCCValues);

    double rST = 0.0;
    double rSR = 0.0;
    double rTR = 0.0;

    bool okST = ComputeSPCC(g_nST, g_sumST_x, g_sumST_y, g_sumST_xy, g_sumST_x2, g_sumST_y2, rST);
    bool okSR = ComputeSPCC(g_nSR, g_sumSR_x, g_sumSR_y, g_sumSR_xy, g_sumSR_x2, g_sumSR_y2, rSR);
    bool okTR = ComputeSPCC(g_nTR, g_sumTR_x, g_sumTR_y, g_sumTR_xy, g_sumTR_x2, g_sumTR_y2, rTR);

    std::cout << "Sample Pearson Correlation Coefficient for "
              << GetMonthName(month) << "\n";

    std::cout << "S_T: ";
    if (okST)
    {
        std::cout << Round2(rST) << "\n";
    }
    else
    {
        std::cout << "No Data\n";
    }

    std::cout << "S_R: ";
    if (okSR)
    {
        std::cout << Round2(rSR) << "\n";
    }
    else
    {
        std::cout << "No Data\n";
    }

    std::cout << "T_R: ";
    if (okTR)
    {
        std::cout << Round2(rTR) << "\n";
    }
    else
    {
        std::cout << "No Data\n";
    }
}

// Menu option 4 and writes to output CSV file.
void Application::DoOption4()
{
    std::cout << "Enter year: ";
    int year = ReadInt();

    std::ofstream out("WindTempSolar.csv");
    if (!out)
    {
        std::cout << "Error creating WindTempSolar.csv\n";
        return;
    }

    out << year << "\n";

    bool yearHasData = false;

    for (int month = 1; month <= 12; month++)
    {
        Vector<float> windValues;
        Vector<float> tempValues;

        g_targetYear = year;
        g_targetMonth = month;
        g_windValues = &windValues;
        g_tempValues = &tempValues;

        m_log.TraverseYear(year, CollectWindTempValues);

        g_windValues = NULL;
        g_tempValues = NULL;

        double totalSolar = UtilityStats::SolarTotal(m_log, year, month);

        bool hasWind = (windValues.GetSize() > 0);
        bool hasTemp = (tempValues.GetSize() > 0);
        bool hasSolar = (totalSolar > 0.0);

        if (!hasWind && !hasTemp && !hasSolar)
        {
            continue;
        }

        yearHasData = true;

        out << GetMonthName(month) << ",";

        if (hasWind)
        {
            float mean = UtilityStats::Mean(windValues);
            float sd = UtilityStats::StDev(windValues, mean);
            float mad = UtilityStats::Mad(windValues, mean);

            out << Round2(mean) << "(" << Round2(sd) << ", " << Round2(mad) << ")";
        }

        out << ",";

        if (hasTemp)
        {
            float mean = UtilityStats::Mean(tempValues);
            float sd = UtilityStats::StDev(tempValues, mean);
            float mad = UtilityStats::Mad(tempValues, mean);

            out << Round2(mean) << "(" << Round2(sd) << ", " << Round2(mad) << ")";
        }

        out << ",";

        if (hasSolar)
        {
            out << Round2(totalSolar);
        }

        out << "\n";
    }

    if (!yearHasData)
    {
        out << "No Data\n";
    }

    out.close();
    std::cout << "WindTempSolar.csv generated successfully.\n";
}