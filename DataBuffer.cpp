#include "DataBuffer.h"

// Node constructor.
DataBuffer::Node::Node(const WeatherRec& rec)
    : data(rec), next(NULL)
{
}

// Default constructor.
DataBuffer::DataBuffer()
    : m_head(NULL), m_tail(NULL), m_size(0)
{
}

// Copy constructor.
DataBuffer::DataBuffer(const DataBuffer& other)
    : m_head(NULL), m_tail(NULL), m_size(0)
{
    Node* current = other.m_head;
    while (current != NULL)
    {
        AddRecord(current->data);
        current = current->next;
    }
}

// Assignment operator.
DataBuffer& DataBuffer::operator=(const DataBuffer& other)
{
    if (this != &other)
    {
        Clear();

        Node* current = other.m_head;
        while (current != NULL)
        {
            AddRecord(current->data);
            current = current->next;
        }
    }

    return *this;
}

// Destructor.
DataBuffer::~DataBuffer()
{
    Clear();
}

// Adds a record to the end of the buffer.
void DataBuffer::AddRecord(const WeatherRec& rec)
{
    Node* newNode = new Node(rec);

    if (m_head == NULL)
    {
        m_head = newNode;
        m_tail = newNode;
    }
    else
    {
        m_tail->next = newNode;
        m_tail = newNode;
    }

    m_size++;
}

// Returns the number of records in the buffer.
int DataBuffer::GetSize() const
{
    return m_size;
}

// Checks whether the buffer is empty.
bool DataBuffer::IsEmpty() const
{
    return m_size == 0;
}

// Clears the buffer.
void DataBuffer::Clear()
{
    DeleteList();
    m_head = NULL;
    m_tail = NULL;
    m_size = 0;
}

// Deletes the linked list.
void DataBuffer::DeleteList()
{
    Node* current = m_head;

    while (current != NULL)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

// Advances a node pointer by a number of steps.
DataBuffer::Node* DataBuffer::Advance(Node* node, int steps) const
{
    while (node != NULL && steps > 0)
    {
        node = node->next;
        steps--;
    }

    return node;
}

// Recursively flushes a list segment to WeatherLog in middle-first order.
void DataBuffer::FlushRangeToLog(WeatherLog& log, Node* start, int count) const
{
    if (start == NULL || count <= 0)
    {
        return;
    }

    int mid = count / 2;
    Node* midNode = Advance(start, mid);

    FlushRangeToLog(log, start, mid);

    if (midNode != NULL)
    {
        log.AddRecord(midNode->data);
        FlushRangeToLog(log, midNode->next, count - mid - 1);
    }
}

// Flushes the entire buffer into WeatherLog.
void DataBuffer::FlushToLog(WeatherLog& log) const
{
    FlushRangeToLog(log, m_head, m_size);
}
