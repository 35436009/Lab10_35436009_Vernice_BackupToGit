#include <iostream>
#include "WeatherRec.h"

using std::cout;
using std::endl;

int main()
{
    cout << "===== Testing WeatherRec =====" << endl;

    Date d(1, 1, 2023);
    Time t(12, 0);

    WeatherRec rec;
    rec.SetDate(d);
    rec.SetTime(t);

    rec.SetSpeed(5.5, true);
    rec.SetSolarRadiation(150.0, true);
    rec.SetTemperature(28.3, true);

    cout << "HasSpeed: " << rec.HasSpeed() << endl;
    cout << "HasSolar: " << rec.HasSolar() << endl;
    cout << "HasTemp: " << rec.HasTemp() << endl;

    cout << "Speed: " << rec.GetSpeed() << endl;
    cout << "Solar: " << rec.GetSolarRadiation() << endl;
    cout << "Temp: " << rec.GetTemperature() << endl;

    cout << "===== WeatherRec Test Complete =====" << endl;
    return 0;
}
