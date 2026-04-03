#ifndef APPLICATION_H
#define APPLICATION_H

#include "WeatherLog.h"
#include <map>
#include "BST.h"

class Application
{
public:
    Application(WeatherLog& log);
    void Run();

private:
    WeatherLog& m_log;


    std::map<int, std::multimap<int, WeatherRec> > m_dataMap;
    BST<int> m_tree;

    void DisplayMenu() const;
    int ReadInt() const;
    const char* GetMonthName(int month) const;

    void DoOption1();
    void DoOption2();
    void DoOption3();
    void DoOption4();

};

#endif
