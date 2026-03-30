#include <iostream>
#include "Time.h"

using std::cout;
using std::endl;

int main()
{
    cout << "===== Testing Time Class =====" << endl;

    Time t1;
    t1.SetHour(10);
    t1.SetMinute(30);

    cout << "Hour: " << t1.GetHour() << endl;
    cout << "Minute: " << t1.GetMinute() << endl;

    Time t2(23, 45);
    cout << "Constructed Time: "
         << t2.GetHour() << ":"
         << t2.GetMinute() << endl;

    cout << "===== Time Test Complete =====" << endl;
    return 0;
}
