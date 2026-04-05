#include "Application.h"
#include "UtilityStats.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "DataLoader.h"
#include <cmath>

// Variable for SPCC
static double sumS = 0, sumT = 0, sumR = 0;
static double sumST = 0, sumSR = 0, sumTR = 0;
static double sumS2 = 0, sumT2 = 0, sumR2 = 0;
static int n = 0;

// Compute SPCC
static double ComputeSPCC(double sumX, double sumY, double sumXY,
                          double sumX2, double sumY2, int n)
{
    double num = n * sumXY - sumX * sumY;
    double denX = n * sumX2 - sumX * sumX;
    double denY = n * sumY2 - sumY * sumY;

    if (denX <= 0 || denY <= 0)
        return 0.0;

    return num / std::sqrt(denX * denY);
}

// Visitor function
void VisitSPCC_ALL(const WeatherRec& rec)
{
    if (rec.HasSpeed() && rec.HasTemp() && rec.HasSolar())
    {
        double S = rec.GetSpeed() * 3.6;
        double T = rec.GetTemperature();
        double R = rec.GetSolarRadiation();

        sumS += S;
        sumT += T;
        sumR += R;

        sumST += S * T;
        sumSR += S * R;
        sumTR += T * R;

        sumS2 += S * S;
        sumT2 += T * T;
        sumR2 += R * R;

        n++;
    }
}


Application::Application()
{
    DataLoader loader;

    if (!loader.ReadDataSources("data/data_source.txt", m_dataMap))
    {
        std::cout << "Warning: Some files failed, continuing...\n";
    }
}

// Main loop
void Application::Run()
{
    int choice;

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
            std::cout << "Exiting...\n"; break;
        default:
            std::cout << "Invalid choice.\n";
        }

    } while (choice != 5);
}

// Menu options
void Application::DisplayMenu() const
{
    std::cout << "1. Wind speed stats (month/year)\n";
    std::cout << "2. Temperature stats (year)\n";
    std::cout << "3. sPCC calculation (month)\n";
    std::cout << "4. Generate WindTempSolar.csv\n";
    std::cout << "5. Exit\n";
}

// Input
int Application::ReadInt() const
{
    int value;
    std::cin >> value;
    return value;
}

// Month name
const char* Application::GetMonthName(int month) const
{
    static const char* names[] =
    {
        "January","February","March","April","May","June",
        "July","August","September","October","November","December"
    };

    return (month >= 1 && month <= 12) ? names[month - 1] : "";
}

// Menu option 1
void Application::DoOption1()
{
    int month, year;

    std::cout << "Enter month (1-12): ";
    month = ReadInt();

    std::cout << "Enter year: ";
    year = ReadInt();

    double mean = UtilityStats::MeanWind(m_dataMap, year, month);
    double sd   = UtilityStats::SDWind(m_dataMap, year, month, mean);

    if (mean == 0.0)
    {
        std::cout << "No data\n";
        return;
    }

    std::cout << std::fixed << std::setprecision(1);

    std::cout << GetMonthName(month) << " " << year << ":\n";
    std::cout << "Average speed: " << mean << " km/h\n";
    std::cout << "Sample stdev: " << sd << "\n";
}

// Menu option 2
void Application::DoOption2()
{
    int year;

    std::cout << "Enter year: ";
    year = ReadInt();

    std::cout << year << "\n";

    std::cout << std::fixed << std::setprecision(1);

    for (int month = 1; month <= 12; month++)
    {
        double mean = UtilityStats::MeanTemp(m_dataMap, year, month);
        double sd   = UtilityStats::SDTemp(m_dataMap, year, month, mean);

        if (mean == 0.0)
        {
            std::cout << GetMonthName(month) << ": No data\n";
        }
        else
        {
            std::cout << GetMonthName(month)
                      << ": average: " << mean
                      << " degrees C, stdev: " << sd << "\n";
        }
    }
}

// Menu option 3
void Application::DoOption3()
{
    int month;
    std::cout << "Enter month (1-12): ";
    month = ReadInt();

    // Reset values
    sumS = sumT = sumR = 0;
    sumST = sumSR = sumTR = 0;
    sumS2 = sumT2 = sumR2 = 0;
    n = 0;

    // Traverse BST
    for (auto itYear = m_dataMap.begin(); itYear != m_dataMap.end(); ++itYear)
    {
        auto itMonth = itYear->second.find(month);
        if (itMonth == itYear->second.end())
            continue;

        itMonth->second.Inorder(VisitSPCC_ALL);
    }

    if (n <= 1)
    {
        std::cout << "No sufficient data\n";
        return;
    }

    // Functions
    double ST = ComputeSPCC(sumS, sumT, sumST, sumS2, sumT2, n);
    double SR = ComputeSPCC(sumS, sumR, sumSR, sumS2, sumR2, n);
    double TR = ComputeSPCC(sumT, sumR, sumTR, sumT2, sumR2, n);

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Sample Pearson Correlation Coefficient for "
              << GetMonthName(month) << "\n";

    std::cout << "S_T: " << ST << "\n";
    std::cout << "S_R: " << SR << "\n";
    std::cout << "T_R: " << TR << "\n";
}

// Option 4
void Application::DoOption4()
{
    int year;

    std::cout << "Enter year: ";
    year = ReadInt();

    std::ofstream out("WindTempSolar.csv");

    if (!out)
    {
        std::cout << "Error creating file\n";
        return;
    }

    out << year << "\n";

    std::cout << std::fixed << std::setprecision(1);

    for (int month = 1; month <= 12; month++)
    {
        double windMean = UtilityStats::MeanWind(m_dataMap, year, month);
        double windSD   = UtilityStats::SDWind(m_dataMap, year, month, windMean);

        double tempMean = UtilityStats::MeanTemp(m_dataMap, year, month);
        double tempSD   = UtilityStats::SDTemp(m_dataMap, year, month, tempMean);

        double solar    = UtilityStats::SolarTotal(m_dataMap, year, month);

        if (windMean == 0 && tempMean == 0 && solar == 0)
            continue;

        out << GetMonthName(month) << ", "
            << windMean << "(" << windSD << "), "
            << tempMean << "(" << tempSD << "), "
            << solar << "\n";
    }

    out.close();
    std::cout << "CSV file generated\n";
}
