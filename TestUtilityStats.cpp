#include <iostream>
#include "UtilityStats.h"
#include "WeatherLog.h"
#include "WeatherRec.h"

using std::cout;
using std::endl;

int main()
{
    cout << "===== Testing UtilityStats =====" << endl;

    WeatherLog log;

    Date d(1, 1, 2023);
    Time t(10, 0);

    WeatherRec r1;
    r1.SetDate(d);
    r1.SetTime(t);
    r1.SetSpeed(5.0, true);
    r1.SetTemperature(30.0, true);
    r1.SetSolarRadiation(200.0, true);

    WeatherRec r2 = r1;
    r2.SetSpeed(7.0, true);
    r2.SetTemperature(28.0, true);
    r2.SetSolarRadiation(180.0, true);

    log.AddRecord(r1);
    log.AddRecord(r2);

    double meanWind = UtilityStats::MeanWind(log, 2023, 1);
    double sdWind   = UtilityStats::SDWind(log, 2023, 1, meanWind);

    cout << "Mean Wind: " << meanWind << endl;
    cout << "SD Wind: " << sdWind << endl;

    double meanTemp = UtilityStats::MeanTemp(log, 2023, 1);
    double sdTemp   = UtilityStats::SDTemp(log, 2023, 1, meanTemp);

    cout << "Mean Temp: " << meanTemp << endl;
    cout << "SD Temp: " << sdTemp << endl;

    double solar = UtilityStats::SolarTotal(log, 2023, 1);
    cout << "Solar Total: " << solar << endl;

    cout << "===== UtilityStats Test Complete =====" << endl;
    return 0;
}
