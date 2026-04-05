#include <iostream>
#include <cassert>
#include "WeatherRec.h"
#include "BST.h"
#include "UtilityStats.h"
#include <map>
#include <cmath>

// --- TEST WEATHERREC ---
void TestWeatherRec()
{
    WeatherRec rec;

    rec.SetSpeed(5.0, true);
    rec.SetTemperature(25.0, true);
    rec.SetSolarRadiation(200.0, true);

    assert(rec.HasSpeed());
    assert(std::fabs(rec.GetSpeed() - 5.0) < 0.0001);

    assert(rec.HasTemp());
    assert(std::fabs(rec.GetTemperature() - 25.0) < 0.0001);

    assert(rec.HasSolar());
    assert(std::fabs(rec.GetSolarRadiation() - 200.0) < 0.0001);

    std::cout << "WeatherRec test passed\n";
}

// --- TEST BST ---
int count = 0;

void VisitCount(const WeatherRec&)
{
    count++;
}

void TestBST()
{
    BST<WeatherRec> tree;

    Date d(1,1,2020);

    WeatherRec r1(d, Time(1,0));
    WeatherRec r2(d, Time(2,0));
    WeatherRec r3(d, Time(3,0));

    tree.Insert(r1);
    tree.Insert(r2);
    tree.Insert(r3);

    count = 0; // IMPORTANT

    tree.Inorder(VisitCount);

    assert(count == 3);

    std::cout << "BST test passed\n";
}

// --- TEST UTILITYSTATS ---
void TestUtilityStats()
{
    std::map<int, std::map<int, BST<WeatherRec>>> dataMap;

    WeatherRec r1, r2;

    // Set values
    r1.SetSpeed(5.0, true);
    r1.SetTemperature(20.0, true);
    r1.SetSolarRadiation(200.0, true);

    r2.SetSpeed(7.0, true);
    r2.SetTemperature(30.0, true);
    r2.SetSolarRadiation(300.0, true);

    // Test date (same month/year)
    Date d;
    d.SetYear(2010);
    d.SetMonth(1);
    d.SetDay(1);

    Time t;
    t.SetHour(0);
    t.SetMinute(0);

    r1.SetDate(d); r1.SetTime(t);
    r2.SetDate(d); r2.SetTime(t);

    dataMap[2020][1].Insert(r1);
    dataMap[2020][1].Insert(r2);

    double meanWind = UtilityStats::MeanWind(dataMap, 2020, 1);
    double meanTemp = UtilityStats::MeanTemp(dataMap, 2020, 1);
    double solar    = UtilityStats::SolarTotal(dataMap, 2020, 1);

    assert(meanWind > 0);
    assert(meanTemp > 0);
    assert(solar > 0);

    std::cout << "UtilityStats test passed\n";
}

// --- MAIN ---
int main()
{
    TestWeatherRec();
    TestBST();
    TestUtilityStats();

    std::cout << "All tests passed successfully!\n";

    return 0;
}
