#ifndef DATABUFFER_H
#define DATABUFFER_H

#include "WeatherRec.h"
#include "WeatherLog.h"

/**
 * @class DataBuffer
 * @brief Temporary linked-list buffer used during data loading.
 *
 * Stores WeatherRec objects before they are inserted into WeatherLog.
 * The buffer helps reduce BST skew by flushing records in a recursive, middle-first order.
 *
 * @author Vernice Foong
 * @version 01
 */

class DataBuffer
{
private:
    struct Node
    {
        WeatherRec data;
        Node* next;
        Node(const WeatherRec& rec);
    };

    Node* m_head;
    Node* m_tail;
    int m_size;

    void DeleteList();
    void FlushRangeToLog(WeatherLog& log, Node* start, int count) const;
    Node* Advance(Node* node, int steps) const;

public:
    /**
    * @brief Default constructor.
    */
    DataBuffer();

    /**
    * @brief Copy constructor.
    * @param other Buffer to copy from.
    */
    DataBuffer(const DataBuffer& other);

    /**
    * @brief Assignment operator.
    * @param other Buffer to assign from.
    * @return Reference to this buffer.
    */
    DataBuffer& operator=(const DataBuffer& other);

    /**
    * @brief Destructor.
    */
    ~DataBuffer();

    /**
    * @brief Adds a weather record to the end of the buffer.
    * @param rec Weather record to store.
    */
    void AddRecord(const WeatherRec& rec);

    /**
    * @brief Returns the number of records currently stored.
    * @return Number of buffered records.
    */
    int GetSize() const;

    /**
    * @brief Checks whether the buffer is empty.
    * @return True if no records are stored, otherwise false.
    */
    bool IsEmpty() const;

    /**
    * @brief Clears all records from the buffer.
    */
    void Clear();

    /**
    * @brief Flushes buffered records into WeatherLog in a recursive middle-first order.
    * @param log WeatherLog to receive the records.
    */
    void FlushToLog(WeatherLog& log) const;
};

#endif
