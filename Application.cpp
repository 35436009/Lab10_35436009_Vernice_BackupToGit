#include "Application.h"
#include "UtilityStats.h"
#include <iostream>
#include <fstream>
#include <cmath>

// Constructor for reference to WeatherLog.
Application::Application(WeatherLog& log)
    : m_log(log) {}

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

    for (int i = 0; i < m_log.GetSize(); i++)
    {
        const WeatherRec& rec = m_log.GetRecord(i);

        if (rec.GetDate().GetYear() == year &&
            rec.GetDate().GetMonth() == month &&
            rec.HasSpeed())
        {
            windValues.Add(static_cast<float>(rec.GetSpeed() * 3.6));
        }
    }

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

        for (int i = 0; i < m_log.GetSize(); i++)
        {
            const WeatherRec& rec = m_log.GetRecord(i);

            if (rec.GetDate().GetYear() == year &&
                rec.GetDate().GetMonth() == month &&
                rec.HasTemp())
            {
                tempValues.Add(static_cast<float>(rec.GetTemperature()));
            }
        }

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
    int month;

    std::cout << "Enter month (1-12): ";
    month = ReadInt();

    if (month < 1 || month > 12)
    {
        std::cout << "Invalid month.\n";
        return;
    }

    double sumST_x = 0, sumST_y = 0, sumST_xy = 0, sumST_x2 = 0, sumST_y2 = 0;
    double sumSR_x = 0, sumSR_y = 0, sumSR_xy = 0, sumSR_x2 = 0, sumSR_y2 = 0;
    double sumTR_x = 0, sumTR_y = 0, sumTR_xy = 0, sumTR_x2 = 0, sumTR_y2 = 0;

    int nST = 0, nSR = 0, nTR = 0;

    for (int i = 0; i < m_log.GetSize(); i++)
    {
        const WeatherRec& rec = m_log.GetRecord(i);

        if (rec.GetDate().GetMonth() != month)
        {
            continue;
        }

        if (rec.HasSpeed() && rec.HasTemp())
        {
            double x = rec.GetSpeed();
            double y = rec.GetTemperature();

            sumST_x += x;
            sumST_y += y;
            sumST_xy += x * y;
            sumST_x2 += x * x;
            sumST_y2 += y * y;
            nST++;
        }

        if (rec.HasSpeed() && rec.HasSolar())
        {
            double x = rec.GetSpeed();
            double y = rec.GetSolarRadiation();

            sumSR_x += x;
            sumSR_y += y;
            sumSR_xy += x * y;
            sumSR_x2 += x * x;
            sumSR_y2 += y * y;
            nSR++;
        }

        if (rec.HasTemp() && rec.HasSolar())
        {
            double x = rec.GetTemperature();
            double y = rec.GetSolarRadiation();

            sumTR_x += x;
            sumTR_y += y;
            sumTR_xy += x * y;
            sumTR_x2 += x * x;
            sumTR_y2 += y * y;
            nTR++;
        }
    }

    double rST = 0.0, rSR = 0.0, rTR = 0.0;
    bool okST = ComputeSPCC(nST, sumST_x, sumST_y, sumST_xy, sumST_x2, sumST_y2, rST);
    bool okSR = ComputeSPCC(nSR, sumSR_x, sumSR_y, sumSR_xy, sumSR_x2, sumSR_y2, rSR);
    bool okTR = ComputeSPCC(nTR, sumTR_x, sumTR_y, sumTR_xy, sumTR_x2, sumTR_y2, rTR);

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

        for (int i = 0; i < m_log.GetSize(); i++)
        {
            const WeatherRec& rec = m_log.GetRecord(i);

            if (rec.GetDate().GetYear() != year ||
                rec.GetDate().GetMonth() != month)
            {
                continue;
            }

            if (rec.HasSpeed())
            {
                windValues.Add(static_cast<float>(rec.GetSpeed() * 3.6));
            }

            if (rec.HasTemp())
            {
                tempValues.Add(static_cast<float>(rec.GetTemperature()));
            }
        }

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