#ifndef APPLICATION_H
#define APPLICATION_H

#include <map>
#include "BST.h"
#include "WeatherRec.h"

class Application
{
public:
    Application();
    void Run();

private:

    std::map<int, std::map<int, BST<WeatherRec> > > m_dataMap;

    void DisplayMenu() const;
    int ReadInt() const;
    const char* GetMonthName(int month) const;

    void DoOption1();
    void DoOption2();
    void DoOption3();
    void DoOption4();

};

#endif
