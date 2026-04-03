#include "WeatherLog.h"

// Default constructor.
WeatherLog::WeatherLog()
{
    // Initialize the internal Vector container.
}

// Adds a WeatherRec into the log.
void WeatherLog::AddRecord(const WeatherRec& rec)
{
    m_records.Add(rec);
}

//Returns number of stored records.
int WeatherLog::GetSize() const
{
    return m_records.GetSize();
}

//Returns record at given index.
const WeatherRec& WeatherLog::GetRecord(int index) const
{
    return m_records[index];
}
