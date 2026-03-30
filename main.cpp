#include "Application.h"
#include "DataLoader.h"
#include <iostream>

int main()
{

    WeatherLog log;       //weather log to store all the data.
    DataLoader loader;    //read all files and load into log

    if (!loader.ReadDataSources("data/data_source.txt", log))
    {
        std::cout << "Loading failed\n";
        return 1;
    }

    Application app(log);   //Application uses the same log
    app.Run();

    return 0;
}
