#include <iostream>
#include "WeatherLog.h"
#include "WeatherRec.h"

using std::cout;
using std::endl;

int main()
{
    cout << "===== Testing WeatherLog =====" << endl;

    WeatherLog log;

    Date d(1, 1, 2023);
    Time t(10, 0);

    WeatherRec rec;
    rec.SetDate(d);
    rec.SetTime(t);
    rec.SetSpeed(3.0, true);

    log.AddRecord(rec);

    cout << "Size after adding 1 record: "
         << log.GetSize() << endl;

    const WeatherRec& stored = log.GetRecord(0);
    cout << "Stored speed: "
         << stored.GetSpeed() << endl;

    cout << "===== WeatherLog Test Complete =====" << endl;
    return 0;
}
