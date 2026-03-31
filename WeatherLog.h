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
 * @version 03
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
     * @brief Returns record at specified logical index.
     *
     * The record is retrieved by traversing the yearly BSTs in order.
     *
     * @param index Logical position in the full dataset.
     * @return WeatherRec at index.
     */
    const WeatherRec& GetRecord(int index) const;

    /**
     * @brief Checks whether a given year exists in the log.
     * @param year Year to look for.
     * @return True if the year exists, otherwise false.
     */
    bool HasYear(int year) const;

private:
    std::map<int, BST<WeatherRec> > m_yearTrees;

    /**
     * @brief Counts how many records exist in a BST.
     * @param tree The tree to count.
     * @return Number of records in the tree.
     */
    int CountTree(const BST<WeatherRec>& tree) const;

    /**
     * @brief Retrieves a record from a BST by traversal index.
     * @param tree The tree to search.
     * @param targetIndex The requested position.
     * @param currentIndex Running count during traversal.
     * @param result The record to return if found.
     * @return True if the record was found, otherwise false.
     */
    bool GetRecordFromTree(const BST<WeatherRec>& tree,
                           int targetIndex,
                           int& currentIndex,
                           WeatherRec& result) const;

    /**
     * @brief Collects records from a BST using inorder traversal.
     * @param tree The tree to traverse.
     * @param targetIndex The requested position.
     * @param currentIndex Running count during traversal.
     * @param result The record to return if found.
     * @return True if the record was found, otherwise false.
     */
    bool GetRecordFromTreeInorder(const BST<WeatherRec>& tree,
                                  int targetIndex,
                                  int& currentIndex,
                                  WeatherRec& result) const;
};

#endif
