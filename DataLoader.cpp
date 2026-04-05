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

// Helper Prototypes
static void InitialiseColumnIndexes(ColumnIndexes& indexes);
static bool GetColumnIndexes(const std::string& headerLine, ColumnIndexes& indexes);

static void ExtractRowFields(const std::string& line,
                             const ColumnIndexes& indexes,
                             std::string& wastField,
                             std::string& speedField,
                             std::string& solarField,
                             std::string& tempField);

static bool ParseWAST(const std::string& wastField, Date& date, Time& time);

static void SetOptionalSpeed(WeatherRec& rec, const std::string& speedField);
static void SetOptionalSolar(WeatherRec& rec, const std::string& solarField);
static void SetOptionalTemp(WeatherRec& rec, const std::string& tempField);

static void FillWeatherRecord(WeatherRec& rec,
                             const std::string& speedField,
                             const std::string& solarField,
                             const std::string& tempField);

static std::string BuildRecordKey(const Date& date, const Time& time);

// Blank Line Check
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

// Read data_source.txt
bool DataLoader::ReadDataSources(const std::string& sourceFile,
    std::map<int, std::map<int, BST<WeatherRec> > > & dataMap)
{
    std::ifstream inFile(sourceFile.c_str());

    if (!inFile.is_open())
    {
        std::cout << "Error opening data_source.txt\n";
        return false;
    }

    std::cout << "Opened data_source.txt\n";

    std::string fileName;
    bool loadedAtLeastOneFile = false;

    while (std::getline(inFile, fileName))
    {
        if (IsBlankLine(fileName))
        {
            continue;
        }

        // call
        if (LoadData(fileName, dataMap))
{
    loadedAtLeastOneFile = true;
}
else
{
    std::cout << "Skipping bad file: " << fileName << "\n";
    // DO NOT stop program
}
    }

    inFile.close();

 return loadedAtLeastOneFile;
}

// Load single CSV
bool DataLoader::LoadData(const std::string& fileName,
    std::map<int, std::map<int, BST<WeatherRec> > >& dataMap)
{
    std::string fullFileName = "data/" + fileName;

    std::cout << "Opening: " << fullFileName << std::endl;

    std::ifstream inFile(fullFileName.c_str());

    if (!inFile.is_open())
    {
        std::cout << "Error opening data file: " << fullFileName << std::endl;

    }

    std::string headerLine;
    if (!std::getline(inFile, headerLine))
    {
        std::cout << "CSV file is empty: " << fileName << std::endl;
        return false;
    }

    ColumnIndexes indexes;
    if (!GetColumnIndexes(headerLine, indexes))
    {
        std::cout << "WAST column not found in file: " << fileName << std::endl;
        return false;
    }

    std::map<std::string, bool> seenRecords;

    std::string line;
    int rowCount = 0;

    while (std::getline(inFile, line))
    {
        if (IsBlankLine(line))
            continue;

        std::string wastField, speedField, solarField, tempField;

        ExtractRowFields(line, indexes, wastField, speedField, solarField, tempField);

        Date date(0, 0, 0);
        Time time(0, 0);

        if (ParseWAST(wastField, date, time))
        {
            std::string key = BuildRecordKey(date, time);

            if (seenRecords.find(key) != seenRecords.end())
                continue;

            seenRecords[key] = true;

            WeatherRec rec(date, time);
            FillWeatherRecord(rec, speedField, solarField, tempField);

            int year = rec.GetDate().GetYear();
            int month = rec.GetDate().GetMonth();

            dataMap[year][month].Insert(rec);

            rowCount++;

            if (rowCount % 5000 == 0)
            {
                std::cout << "Processed " << rowCount
                          << " rows from " << fileName << std::endl;
            }
        }
    }

    return true;
}

// Column Helpers
static void InitialiseColumnIndexes(ColumnIndexes& indexes)
{
    indexes.wastIndex = -1;
    indexes.speedIndex = -1;
    indexes.solarIndex = -1;
    indexes.tempIndex = -1;
}

static bool GetColumnIndexes(const std::string& headerLine, ColumnIndexes& indexes)
{
    InitialiseColumnIndexes(indexes);

    std::stringstream ss(headerLine);
    std::string field;
    int col = 0;

    while (std::getline(ss, field, DELIMITER))
    {
        if (field == "WAST") indexes.wastIndex = col;
        else if (field == "S" || field == "Speed") indexes.speedIndex = col;
        else if (field == "SR" || field == "Solar") indexes.solarIndex = col;
        else if (field == "T" || field == "Temp") indexes.tempIndex = col;

        col++;
    }

    return indexes.wastIndex != -1;
}

// Row Extraction
static void ExtractRowFields(const std::string& line,
                             const ColumnIndexes& indexes,
                             std::string& wastField,
                             std::string& speedField,
                             std::string& solarField,
                             std::string& tempField)
{
    std::stringstream ss(line);
    std::string field;
    int i = 0;

    while (std::getline(ss, field, DELIMITER))
    {
        if (i == indexes.wastIndex) wastField = field;
        if (i == indexes.speedIndex) speedField = field;
        if (i == indexes.solarIndex) solarField = field;
        if (i == indexes.tempIndex) tempField = field;
        i++;
    }
}

// Parse DateTime
static bool ParseWAST(const std::string& wastField, Date& date, Time& time)
{
    if (wastField.empty() || wastField == "NA") return false;

    std::stringstream ss(wastField);
    std::string d, t;
    ss >> d >> t;

    int day, month, year, hour, minute;

    char slash, colon;
    std::stringstream(d) >> day >> slash >> month >> slash >> year;
    std::stringstream(t) >> hour >> colon >> minute;

    date = Date(day, month, year);
    time = Time(hour, minute);

    return true;
}

// Optional setters
static void SetOptionalSpeed(WeatherRec& rec, const std::string& f)
{
    if (f.empty() || f == "NA") rec.SetSpeed(0, false);
    else { double v; std::stringstream(f) >> v; rec.SetSpeed(v, true); }
}

static void SetOptionalSolar(WeatherRec& rec, const std::string& f)
{
    if (f.empty() || f == "NA") rec.SetSolarRadiation(0, false);
    else { double v; std::stringstream(f) >> v; rec.SetSolarRadiation(v, true); }
}

static void SetOptionalTemp(WeatherRec& rec, const std::string& f)
{
    if (f.empty() || f == "NA") rec.SetTemperature(0, false);
    else { double v; std::stringstream(f) >> v; rec.SetTemperature(v, true); }
}

static void FillWeatherRecord(WeatherRec& rec,
                             const std::string& s,
                             const std::string& sr,
                             const std::string& t)
{
    SetOptionalSpeed(rec, s);
    SetOptionalSolar(rec, sr);
    SetOptionalTemp(rec, t);
}

// Key builder
static std::string BuildRecordKey(const Date& d, const Time& t)
{
    std::stringstream ss;
    ss << d.GetDay() << "/" << d.GetMonth() << "/" << d.GetYear()
       << " " << t.GetHour() << ":" << t.GetMinute();
    return ss.str();
}
