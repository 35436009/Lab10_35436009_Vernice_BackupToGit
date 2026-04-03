#include "Application.h"
#include "UtilityStats.h"
#include <iostream>
#include <fstream>
#include "BST.h"
#include <cmath>
#include <iomanip>

//Helper for MAD
static double CalculateMAD_Map(const std::multimap<int, WeatherRec>& monthMap, int month, int type, double mean)
{
    std::pair<std::multimap<int, WeatherRec>::const_iterator,
              std::multimap<int, WeatherRec>::const_iterator> range = monthMap.equal_range(month);

    double sum = 0.0;
    int count = 0;

    for (std::multimap<int, WeatherRec>::const_iterator it = range.first; it != range.second; it++)
    {
        const WeatherRec& rec = it->second;
        double value = 0.0;
        bool valid = false;

        if (type == 1 && rec.HasSpeed())
        {
            value = rec.GetSpeed();
            valid = true;
        }
        else if (type == 2 && rec.HasTemp())
        {
            value = rec.GetTemperature();
            valid = true;
        }
        else if (type == 3 && rec.HasSolar())
        {
            value = rec.GetSolarRadiation();
            valid = true;
        }

        if (valid)
        {
            sum += std::abs(value - mean);
            count++;
        }
    }

    if (count > 0)
    {
        return sum / count;
    }
    else
    {
        return 0.0;
    }
}

//Helper for Mean
static double CalculateMean(double sum, int count)
{
    if (count > 0)
    {
        return sum / count;
    }
    else
    {
        return 0.0;
    }
}

//Helper for SD
static double CalculateSD(double sumSquares, int count)
{
    if (count > 0)
    {
        return std::sqrt(sumSquares / count);
    }
    else
    {
        return 0.0;
    }
}

//Helper for VarianceSum
static double CalculateVarianceSum(const std::multimap<int, WeatherRec>& monthMap,
                                   int month,
                                   int type,
                                   double mean)
{
    std::pair<std::multimap<int, WeatherRec>::const_iterator,
              std::multimap<int, WeatherRec>::const_iterator> range = monthMap.equal_range(month);

    double sum = 0.0;

    for (std::multimap<int, WeatherRec>::const_iterator it = range.first; it != range.second; it++)
    {
        const WeatherRec& rec = it->second;
        double value = 0.0;
        bool valid = false;

        if (type == 1)
        {
            if (rec.HasSpeed())
            {
                value = rec.GetSpeed();
                valid = true;
            }
        }
        else if (type == 2)
        {
            if (rec.HasTemp())
            {
                value = rec.GetTemperature();
                valid = true;
            }
        }
        else if (type == 3)
        {
            if (rec.HasSolar())
            {
                value = rec.GetSolarRadiation();
                valid = true;
            }
        }

        if (valid)
        {
            sum += (value - mean) * (value - mean);
        }
    }

    return sum;
}

// Constructor for reference to WeatherLog.
Application::Application(WeatherLog& log)
    : m_log(log)
{
    for (int i = 0; i < m_log.GetSize(); i++)
    {
        const WeatherRec& rec = m_log.GetRecord(i);

        int year = rec.GetDate().GetYear();
        int month = rec.GetDate().GetMonth();

        m_dataMap[year].insert(std::make_pair(month, rec));

        if (!m_tree.Search(year))
        {
            m_tree.Insert(year);
        }
    }
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
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    if (month >= 1 && month <= 12)
    {
        return names[month - 1];
    }
    else
    {
        return "";
    }
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
    }
    else
    {
        std::map<int, std::multimap<int, WeatherRec> >::iterator itYear = m_dataMap.find(year);

        if (itYear == m_dataMap.end())
        {
            std::cout << GetMonthName(month) << " " << year << ": No Data\n";
        }
        else
        {
            std::multimap<int, WeatherRec>& monthMap = itYear->second;
            std::pair<std::multimap<int, WeatherRec>::iterator,
                      std::multimap<int, WeatherRec>::iterator> range = monthMap.equal_range(month);

            double sum = 0.0;
            int count = 0;

            for (std::multimap<int, WeatherRec>::iterator it = range.first; it != range.second; it++)
            {
                const WeatherRec& rec = it->second;

                if (rec.GetDate().GetYear() == year && rec.HasSpeed())
                {
                    sum += rec.GetSpeed();
                    count++;
                }
            }

            if (count == 0)
            {
                std::cout << GetMonthName(month) << " " << year << ": No Data\n";
            }
            else
            {
                double mean = CalculateMean(sum, count);
                double variance = 0.0;

                for (std::multimap<int, WeatherRec>::iterator it = range.first; it != range.second; it++)
                {
                    const WeatherRec& rec = it->second;

                    if (rec.GetDate().GetYear() == year && rec.HasSpeed())
                    {
                        variance += (rec.GetSpeed() - mean) * (rec.GetSpeed() - mean);
                    }
                }

                double sd = CalculateSD(variance, count);

                std::cout << GetMonthName(month) << " " << year << ":\n";
                std::cout << "Average speed: " << mean << " km/h\n";
                std::cout << "Sample stdev: " << sd << "\n";
            }
        }
    }
}

// Menu option 2 for temperature stats.
void Application::DoOption2()
{
    std::cout << "Enter year: ";
    int year = ReadInt();

    std::cout << year << "\n";

    for (int month = 1; month <= 12; month++)
    {
        double mean = UtilityStats::MeanTemp(m_log, year, month);

        if (mean == 0.0)
        {
            std::cout << GetMonthName(month) << ": No Data\n";
        }
        else
        {
            double sd = UtilityStats::SDTemp(m_log, year, month, mean);

            std::cout << GetMonthName(month)
                      << ": average: " << mean
                      << " degrees C, stdev: " << sd
                      << "\n";
        }
    }
}

// Option 3
void Application::DoOption3()
{
    int month;

    std::cout << "Enter month (1-12): ";
    month = ReadInt();

    if (month < 1 || month > 12)
    {
        std::cout << "Invalid month\n";
    }
    else
    {
        double sumS = 0.0;
        double sumT = 0.0;
        double sumR = 0.0;
        double sumST = 0.0;
        double sumSR = 0.0;
        double sumTR = 0.0;
        double sumS2 = 0.0;
        double sumT2 = 0.0;
        double sumR2 = 0.0;
        int n = 0;

        for (std::map<int, std::multimap<int, WeatherRec> >::iterator yearPair = m_dataMap.begin();
             yearPair != m_dataMap.end();
             yearPair++)
        {
            std::multimap<int, WeatherRec>& monthMap = yearPair->second;
            std::pair<std::multimap<int, WeatherRec>::iterator,
                      std::multimap<int, WeatherRec>::iterator> range = monthMap.equal_range(month);

            for (std::multimap<int, WeatherRec>::iterator it = range.first; it != range.second; it++)
            {
                const WeatherRec& rec = it->second;

                if (rec.HasSpeed() && rec.HasTemp() && rec.HasSolar())
                {
                    double S = rec.GetSpeed();
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
        }

        if (n < 2)
        {
            std::cout << "Not enough data\n";
        }
        else
        {
            double numerator;
            double denominator;

            numerator = n * sumST - sumS * sumT;
            denominator = std::sqrt((n * sumS2 - sumS * sumS) * (n * sumT2 - sumT * sumT));
            double ST;
            if (denominator == 0.0)
            {
                ST = 0.0;
            }
            else
            {
                ST = numerator / denominator;
            }

            numerator = n * sumSR - sumS * sumR;
            denominator = std::sqrt((n * sumS2 - sumS * sumS) * (n * sumR2 - sumR * sumR));
            double SR;
            if (denominator == 0.0)
            {
                SR = 0.0;
            }
            else
            {
                SR = numerator / denominator;
            }

            numerator = n * sumTR - sumT * sumR;
            denominator = std::sqrt((n * sumT2 - sumT * sumT) * (n * sumR2 - sumR * sumR));
            double TR;
            if (denominator == 0.0)
            {
                TR = 0.0;
            }
            else
            {
                TR = numerator / denominator;
            }

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "\nSample Pearson Correlation Coefficient for "
                      << GetMonthName(month) << "\n";

            std::cout << "S_T: " << ST << "\n";
            std::cout << "S_R: " << SR << "\n";
            std::cout << "T_R: " << TR << "\n";
        }
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
    }
    else
    {
        out << year << "\n";

        bool yearHasData = false;

        for (int month = 1; month <= 12; month++)
        {
            if (UtilityStats::HasAnyDataForMonth(m_log, year, month))
            {
                yearHasData = true;

                std::map<int, std::multimap<int, WeatherRec> >::iterator itYear = m_dataMap.find(year);

                if (itYear != m_dataMap.end())
                {
                    std::multimap<int, WeatherRec>& monthMap = itYear->second;
                    std::pair<std::multimap<int, WeatherRec>::iterator,
                              std::multimap<int, WeatherRec>::iterator> range = monthMap.equal_range(month);

                    double sumWind = 0.0;
                    int countWind = 0;
                    double sumTemp = 0.0;
                    int countTemp = 0;
                    double sumSolar = 0.0;

                    for (std::multimap<int, WeatherRec>::iterator it = range.first; it != range.second; it++)
                    {
                        const WeatherRec& rec = it->second;

                        if (rec.HasSpeed())
                        {
                            sumWind += rec.GetSpeed();
                            countWind++;
                        }

                        if (rec.HasTemp())
                        {
                            sumTemp += rec.GetTemperature();
                            countTemp++;
                        }

                        if (rec.HasSolar())
                        {
                            sumSolar += rec.GetSolarRadiation();
                        }
                    }

                    double meanWind = CalculateMean(sumWind, countWind);
                    double meanTemp = CalculateMean(sumTemp, countTemp);
                    double totalSolar = sumSolar;

                    out << GetMonthName(month) << ",";

                    if (meanWind != 0.0)
                    {
                        double varianceWind = CalculateVarianceSum(monthMap, month, 1, meanWind);
                        double sdWind = CalculateSD(varianceWind, countWind);
                        double madWind = CalculateMAD_Map(monthMap, month, 1, meanWind);
                        out << meanWind << "(" << sdWind << "," << madWind << ")";
                    }

                    out << ",";

                    if (meanTemp != 0.0)
                    {
                        double varianceTemp = CalculateVarianceSum(monthMap, month, 2, meanTemp);
                        double sdTemp = CalculateSD(varianceTemp, countTemp);
                        double madTemp = CalculateMAD_Map(monthMap, month, 2, meanTemp);
                        out << meanTemp << "(" << sdTemp << "," << madTemp << ")";
                    }

                    out << ",";

                    if (totalSolar != 0.0)
                    {
                        double madSolar = CalculateMAD_Map(monthMap, month, 3, totalSolar);
                        out << totalSolar << "(0," << madSolar << ")";
                    }

                    out << "\n";
                }
            }
        }

        if (!yearHasData)
        {
            out << "No Data\n";
        }

        out.close();
        std::cout << "WindTempSolar.csv generated successfully.\n";
    }
}




