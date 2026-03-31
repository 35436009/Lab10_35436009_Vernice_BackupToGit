#include "WeatherLog.h"

// Default constructor.
WeatherLog::WeatherLog()
    : m_totalRecords(0)
{
    // Map starts empty and trees are created on demand.
}

// Adds a WeatherRec into the log.
void WeatherLog::AddRecord(const WeatherRec& rec)
{
    int year = rec.GetDate().GetYear();

    if (m_yearTrees.find(year) == m_yearTrees.end())
    {
        m_yearTrees.insert(std::make_pair(year, BST<WeatherRec>()));
    }

    m_yearTrees[year].Insert(rec);
    m_totalRecords++;
}

// Returns number of stored records across all years.
int WeatherLog::GetSize() const
{
    return m_totalRecords;
}

// Checks whether a given year exists in the log.
bool WeatherLog::HasYear(int year) const
{
    return m_yearTrees.find(year) != m_yearTrees.end();
}

// Checks whether a record with the same date and time exists.
bool WeatherLog::RecordExists(const Date& date, const Time& time) const
{
    std::map<int, BST<WeatherRec> >::const_iterator it = m_yearTrees.find(date.GetYear());

    if (it == m_yearTrees.end())
    {
        return false;
    }

    WeatherRec probe(date, time);
    return it->second.Search(probe);
}

// Traverses all records for a given year in sorted order.
void WeatherLog::TraverseYear(int year, void (*visit)(const WeatherRec&)) const
{
    std::map<int, BST<WeatherRec> >::const_iterator it = m_yearTrees.find(year);

    if (it != m_yearTrees.end())
    {
        it->second.Inorder(visit);
    }
}

// Retrieves the BST for a given year.
BST<WeatherRec>* WeatherLog::GetYearTree(int year)
{
    std::map<int, BST<WeatherRec> >::iterator it = m_yearTrees.find(year);

    if (it == m_yearTrees.end())
    {
        return NULL;
    }

    return &(it->second);
}

// Retrieves the BST for a given year.
const BST<WeatherRec>* WeatherLog::GetYearTree(int year) const
{
    std::map<int, BST<WeatherRec> >::const_iterator it = m_yearTrees.find(year);

    if (it == m_yearTrees.end())
    {
        return NULL;
    }

    return &(it->second);
}
