#ifndef WEATHERLOG_H
#define WEATHERLOG_H

#include "Vector.h"
#include "WeatherRec.h"

/**
 * @class WeatherLog
 * @brief Stores all WeatherRec records loaded from CSV.
 *
 * This class encapsulates the dynamic container of weather records.
 *
 * @author Vernice Foong
 * @version 02
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
     * @param rec WeatherRec object.
     */
    void AddRecord(const WeatherRec& rec);

    /**
     * @brief Returns number of records stored.
     * @return size of log.
     */
    int GetSize() const;

    /**
     * @brief Returns record at specified index.
     * @param index position in vector.
     * @return WeatherRec at index.
     */
    const WeatherRec& GetRecord(int index) const;

private:
    Vector<WeatherRec> m_records;
};

#endif
