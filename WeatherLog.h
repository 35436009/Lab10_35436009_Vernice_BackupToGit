#ifndef WEATHERLOG_H
#define WEATHERLOG_H

#include "BST.h"
#include "WeatherRec.h"
#include <map>

/**
 * @class WeatherLog
 * @brief Stores and organises WeatherRec records loaded from CSV.
 *
 * This class acts as the central storage for weather data. Map of BSTs.
 * Records are grouped by year in a map, and each year stores its
 * records inside a BST for ordered processing.
 *
 * @author Vernice Foong
 * @version 06
 */
class WeatherLog
{
public:

    /**
     * @brief Default constructor.
     */
    WeatherLog();

    /**
     * @brief Adds a weather record to the log.
     *
     * The record is stored in the BST associated with its year.
     *
     * @param rec WeatherRec object.
     */
    void AddRecord(const WeatherRec& rec);

    /**
     * @brief Returns number of records stored across all years.
     * @return Total number of records in the log.
     */
    int GetSize() const;

    /**
     * @brief Checks whether a given year exists in the log.
     * @param year Year to look for.
     * @return True if the year exists, otherwise false.
     */
    bool HasYear(int year) const;

    /**
     * @brief Checks whether a record with the same date and time exists.
     * @param date Date to check.
     * @param time Time to check.
     * @return True if a matching record exists, otherwise false.
     */
    bool RecordExists(const Date& date, const Time& time) const;

    /**
     * @brief Traverses all records for a given year in sorted order.
     *
     * If the year does not exist, nothing is visited.
     *
     * @param year Year to traverse.
     * @param visit Callback function applied to each record.
     */
    void TraverseYear(int year, void (*visit)(const WeatherRec&)) const;

    /**
     * @brief Traverses all records across all years in sorted order.
     *
     * Records are visited year by year in ascending order.
     *
     * @param visit Callback function applied to each record.
     */
    void TraverseAllYears(void (*visit)(const WeatherRec&)) const;

private:
    std::map<int, BST<WeatherRec> > m_yearTrees;
    int m_totalRecords;

};

#endif
