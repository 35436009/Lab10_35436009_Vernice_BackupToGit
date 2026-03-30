#include <iostream>
#include "Date.h"

using std::cout;
using std::endl;

int main()
{
    cout << "===== Testing Date Class =====" << endl;

    Date d1;
    d1.SetDay(15);
    d1.SetMonth(3);
    d1.SetYear(2024);

    cout << "Day: " << d1.GetDay() << endl;
    cout << "Month: " << d1.GetMonth() << endl;
    cout << "Year: " << d1.GetYear() << endl;

    Date d2(1, 1, 2000);
    cout << "Constructed Date: "
         << d2.GetDay() << "/"
         << d2.GetMonth() << "/"
         << d2.GetYear() << endl;

    cout << "===== Date Test Complete =====" << endl;
    return 0;
}
