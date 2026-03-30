#ifndef DATALOADER_H
#define DATALOADER_H

#include "WeatherLog.h"
#include <string>

/**
 * @class DataLoader
 * @brief Loads weather data from source and CSV files into WeatherLog.
 *
 * Responsibilities:
 * - Open data_source.txt
 * - Read each CSV file listed
 * - Parse weather records
 * - Skip blank or duplicate records
 * - Store valid records into WeatherLog
 *
 * @author Vernice Foong
 * @version 02
 */
class DataLoader
{
public:
    /**
     * @brief Opens data_source.txt and loads each CSV file listed in it.
     *
     * @param sourceFile Name of the source text file.
     * @param log WeatherLog object to store all loaded records.
     * @return true if at least one file is loaded; otherwise false.
     */
    bool ReadDataSources(const std::string& sourceFile, WeatherLog& log);

private:
    /**
     * @brief Opens one CSV file and loads its records into WeatherLog.
     *
     * @param fileName Name of the CSV file.
     * @param log WeatherLog object to store records.
     * @return true if the file loads successfully; otherwise false.
     */
    bool LoadData(const std::string& fileName, WeatherLog& log);

    /**
     * @brief Checks if a line is blank or contains only commas/spaces.
     *
     * @param line Input line from file.
     * @return true if line is blank; otherwise false.
     */
    bool IsBlankLine(const std::string& line) const;

    /**
     * @brief Checks if a record with the same date and time already exists.
     *
     * @param log WeatherLog to search.
     * @param date Date of the record.
     * @param time Time of the record.
     * @return true if duplicate exists; otherwise false.
     */
    bool RecordExists(const WeatherLog& log, const Date& date, const Time& time) const;
};

#endif