#include "DataLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

// Used to separate CSV fields.
const char DELIMITER = ',';

// Stores the column positions found in a CSV header.
struct ColumnIndexes
{
    int wastIndex;
    int speedIndex;
    int solarIndex;
    int tempIndex;
};

// My helper prototypes
// Sets all column indexes to not found.
static void InitialiseColumnIndexes(ColumnIndexes& indexes);

// Reads the header row and finds the needed column positions.
static bool GetColumnIndexes(const std::string& headerLine, ColumnIndexes& indexes);

// Reads one row and extracts only the required fields.
static void ExtractRowFields(const std::string& line,
                             const ColumnIndexes& indexes,
                             std::string& wastField,
                             std::string& speedField,
                             std::string& solarField,
                             std::string& tempField);

// Parses the WAST field into Date and Time objects.
static bool ParseWAST(const std::string& wastField, Date& date, Time& time);

// Stores one optional speed value into the record.
static void SetOptionalSpeed(WeatherRec& rec, const std::string& speedField);

// Stores one optional solar value into the record.
static void SetOptionalSolar(WeatherRec& rec, const std::string& solarField);

// Stores one optional temperature value into the record.
static void SetOptionalTemp(WeatherRec& rec, const std::string& tempField);

// Fills the record with optional numeric values.
static void FillWeatherRecord(WeatherRec& rec,
                              const std::string& speedField,
                              const std::string& solarField,
                              const std::string& tempField);

// Builds a unique key for duplicate detection.
static std::string BuildRecordKey(const Date& date, const Time& time);

// Checks if a line is blank or contains only commas/spaces.
bool DataLoader::IsBlankLine(const std::string& line) const
{
    for (int i = 0; i < (int)line.length(); i++)
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != DELIMITER)
        {
            return false;
        }
    }

    return true;
}

// Opens data_source.txt and loads every CSV file listed.
bool DataLoader::ReadDataSources(const std::string& sourceFile, WeatherLog& log)
{
    std::ifstream inFile(sourceFile.c_str());

    if (!inFile.is_open())
    {
        std::cout << "Error opening data_source.txt\n";
        return false;
    }
    else
    {
        std::cout << "Opened data_source.txt" << std::endl;
    }

    std::string fileName;
    bool loadedAtLeastOneFile = false;

    while (std::getline(inFile, fileName))
    {
        if (IsBlankLine(fileName))
        {
            // Blank line in source file, do nothing.
        }
        else
        {
            if (LoadData(fileName, log))
            {
                loadedAtLeastOneFile = true;
            }
            else
            {
                std::cout << "Error opening CSV file: " << fileName << "\n";
                inFile.close();
                return false;
            }
        }
    }

    inFile.close();

    if (loadedAtLeastOneFile)
    {
        return true;
    }
    else
    {
        std::cout << "No CSV files in data_source.txt\n";
        return false;
    }
}

// Opens one CSV file and loads all valid records into WeatherLog.
bool DataLoader::LoadData(const std::string& fileName, WeatherLog& log)
{
    std::string fullFileName = "data/" + fileName;
    std::ifstream inFile(fullFileName.c_str());

    if (!inFile.is_open())
    {
        std::cout << "Error opening data file: " << fileName << std::endl;
        return false;
    }

    std::string headerLine;
    if (!std::getline(inFile, headerLine))
    {
        std::cout << "CSV file is empty: " << fileName << std::endl;
        inFile.close();
        return false;
    }

    ColumnIndexes indexes;
    if (!GetColumnIndexes(headerLine, indexes))
    {
        std::cout << "Required column WAST not found in file: " << fileName << std::endl;
        inFile.close();
        return false;
    }

    std::map<std::string, bool> seenRecords;

    std::string line;
    int rowCount = 0;

    while (std::getline(inFile, line))
    {
        if (IsBlankLine(line))
        {
            // Blank data row, skip.
        }
        else
        {
            std::string wastField;
            std::string speedField;
            std::string solarField;
            std::string tempField;

            ExtractRowFields(line, indexes, wastField, speedField, solarField, tempField);

            Date date(0, 0, 0);
            Time time(0, 0);

            if (ParseWAST(wastField, date, time))
            {
                std::string recordKey = BuildRecordKey(date, time);

                if (seenRecords.find(recordKey) != seenRecords.end())
                {
                    // Duplicate row, skip it.
                }
                else
                {
                    seenRecords.insert(std::make_pair(recordKey, true));

                    WeatherRec rec(date, time);
                    FillWeatherRecord(rec, speedField, solarField, tempField);
                    log.AddRecord(rec);

                    rowCount++;

                    if (rowCount % 5000 == 0)
                    {
                        std::cout << "Processed " << rowCount
                                  << " rows from " << fileName << std::endl;
                    }
                }
            }
            else
            {
                // Invalid WAST field, skip.
            }
        }
    }

    inFile.close();
    return true;
}

// Sets all column indexes to not found.
static void InitialiseColumnIndexes(ColumnIndexes& indexes)
{
    indexes.wastIndex = -1;
    indexes.speedIndex = -1;
    indexes.solarIndex = -1;
    indexes.tempIndex = -1;
}

// Reads the header row and finds the needed column positions.
static bool GetColumnIndexes(const std::string& headerLine, ColumnIndexes& indexes)
{
    InitialiseColumnIndexes(indexes);

    std::stringstream headerStream(headerLine);
    std::string field;
    int col = 0;

    while (std::getline(headerStream, field, DELIMITER))
    {
        if (field == "WAST")
        {
            indexes.wastIndex = col;
        }
        else if (field == "S" || field == "Speed")
        {
            indexes.speedIndex = col;
        }
        else if (field == "SR" || field == "Solar")
        {
            indexes.solarIndex = col;
        }
        else if (field == "T" || field == "Temp")
        {
            indexes.tempIndex = col;
        }

        col++;
    }

    if (indexes.wastIndex == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Reads one row and extracts only the required fields.
static void ExtractRowFields(const std::string& line,
                             const ColumnIndexes& indexes,
                             std::string& wastField,
                             std::string& speedField,
                             std::string& solarField,
                             std::string& tempField)
{
    wastField = "";
    speedField = "";
    solarField = "";
    tempField = "";

    std::stringstream rowStream(line);
    std::string currentField;
    int currentIndex = 0;

    while (std::getline(rowStream, currentField, DELIMITER))
    {
        if (currentIndex == indexes.wastIndex)
        {
            wastField = currentField;
        }
        else if (currentIndex == indexes.speedIndex)
        {
            speedField = currentField;
        }
        else if (currentIndex == indexes.solarIndex)
        {
            solarField = currentField;
        }
        else if (currentIndex == indexes.tempIndex)
        {
            tempField = currentField;
        }

        currentIndex++;
    }
}

// Parses the WAST field into Date and Time objects.
static bool ParseWAST(const std::string& wastField, Date& date, Time& time)
{
    if (wastField == "" || wastField == "NA")
    {
        return false;
    }

    std::stringstream wastStream(wastField);
    std::string datePart;
    std::string timePart;

    wastStream >> datePart >> timePart;

    if (datePart == "" || timePart == "")
    {
        return false;
    }

    std::stringstream dateStream(datePart);
    std::string dayText;
    std::string monthText;
    std::string yearText;

    std::getline(dateStream, dayText, '/');
    std::getline(dateStream, monthText, '/');
    std::getline(dateStream, yearText, '/');

    if (dayText == "" || monthText == "" || yearText == "")
    {
        return false;
    }

    std::stringstream timeStream(timePart);
    std::string hourText;
    std::string minuteText;

    std::getline(timeStream, hourText, ':');
    std::getline(timeStream, minuteText, ':');

    if (hourText == "" || minuteText == "")
    {
        return false;
    }

    int day = 0;
    int month = 0;
    int year = 0;
    int hour = 0;
    int minute = 0;

    std::stringstream(dayText) >> day;
    std::stringstream(monthText) >> month;
    std::stringstream(yearText) >> year;
    std::stringstream(hourText) >> hour;
    std::stringstream(minuteText) >> minute;

    date = Date(day, month, year);
    time = Time(hour, minute);

    return true;
}

// Stores one optional speed value into the record.
static void SetOptionalSpeed(WeatherRec& rec, const std::string& speedField)
{
    if (speedField == "" || speedField == "NA")
    {
        rec.SetSpeed(0.0, false);
    }
    else
    {
        double speed = 0.0;
        std::stringstream(speedField) >> speed;
        rec.SetSpeed(speed, true);
    }
}

// Stores one optional solar value into the record.
static void SetOptionalSolar(WeatherRec& rec, const std::string& solarField)
{
    if (solarField == "" || solarField == "NA")
    {
        rec.SetSolarRadiation(0.0, false);
    }
    else
    {
        double solar = 0.0;
        std::stringstream(solarField) >> solar;
        rec.SetSolarRadiation(solar, true);
    }
}

// Stores one optional temperature value into the record.
static void SetOptionalTemp(WeatherRec& rec, const std::string& tempField)
{
    if (tempField == "" || tempField == "NA")
    {
        rec.SetTemperature(0.0, false);
    }
    else
    {
        double temp = 0.0;
        std::stringstream(tempField) >> temp;
        rec.SetTemperature(temp, true);
    }
}

// Fills the record with optional numeric values.
static void FillWeatherRecord(WeatherRec& rec,
                              const std::string& speedField,
                              const std::string& solarField,
                              const std::string& tempField)
{
    SetOptionalSpeed(rec, speedField);
    SetOptionalSolar(rec, solarField);
    SetOptionalTemp(rec, tempField);
}

// Builds a unique key for duplicate detection.
static std::string BuildRecordKey(const Date& date, const Time& time)
{
    std::stringstream keyStream;
    keyStream << date.GetDay() << '/'
              << date.GetMonth() << '/'
              << date.GetYear() << ' '
              << time.GetHour() << ':'
              << time.GetMinute();
    return keyStream.str();
}