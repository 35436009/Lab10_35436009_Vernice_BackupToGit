#include "WeatherLog.h"

// Default constructor.
WeatherLog::WeatherLog()
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
}

// Returns number of stored records across all years.
int WeatherLog::GetSize() const
{
    int total = 0;

    for (std::map<int, BST<WeatherRec> >::const_iterator it = m_yearTrees.begin();
         it != m_yearTrees.end();
         ++it)
    {
        total += CountTree(it->second);
    }

    return total;
}

// Returns record at given logical index.
const WeatherRec& WeatherLog::GetRecord(int index) const
{
    static WeatherRec dummy;
    int currentIndex = 0;

    if (index < 0)
    {
        return dummy;
    }

    for (std::map<int, BST<WeatherRec> >::const_iterator it = m_yearTrees.begin();
         it != m_yearTrees.end();
         ++it)
    {
        WeatherRec result;

        if (GetRecordFromTree(it->second, index, currentIndex, result))
        {
            return result;
        }
    }

    return dummy;
}

// Checks whether a given year exists in the log.
bool WeatherLog::HasYear(int year) const
{
    return m_yearTrees.find(year) != m_yearTrees.end();
}

// Counts how many records exist in a BST.
int WeatherLog::CountTree(const BST<WeatherRec>& tree) const
{
    int count = 0;
    int currentIndex = 0;
    WeatherRec result;

    while (GetRecordFromTreeInorder(tree, count, currentIndex, result))
    {
        count++;
    }

    return count;
}

// Retrieves a record from a BST by traversal index.
bool WeatherLog::GetRecordFromTree(const BST<WeatherRec>& tree,
                                  int targetIndex,
                                  int& currentIndex,
                                  WeatherRec& result) const
{
    return GetRecordFromTreeInorder(tree, targetIndex, currentIndex, result);
}

// Collects records from a BST using inorder traversal.
bool WeatherLog::GetRecordFromTreeInorder(const BST<WeatherRec>& tree,
                                          int targetIndex,
                                          int& currentIndex,
                                          WeatherRec& result) const
{
    struct VisitorState
    {
        int target;
        int* current;
        WeatherRec* found;
        bool* ok;
    };

    return false;
}
