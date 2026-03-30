#ifndef VECTOR_H
#define VECTOR_H
#include <vector>

template <class T>
class Vector
{
public:

    Vector() {};
    Vector(int n);          //Parameterized constructor
    ~Vector() {};

    //CRUD
    const T & operator[](int index) const;      //R - Index operator for read only
    T & operator[](int index);                  //U - Index operator for modification

    bool Insert(int index, const T & item);     //C
    //bool Delete(int index);                   //D

    bool Add(const T & item);       //Additional insert method, but return same insert
    bool Erase(int index);          //to delete a specific index.
    bool PopBack();                 //removes only the last element.
    void Clear();                   //Reset the vector

    int GetSize() const;            //Returns number of elements stored currently

private:
    std::vector<T> m_vector;
};

// Implementation

template <class T>
Vector<T>::Vector(int n)
{
    if (n > 0)
    {
        m_vector.resize(n);
    }
}

template <class T>
bool Vector<T>::Insert(int index, const T& item)
{
    if(index < 0 || index > GetSize())
    {
        return false;
    }
    else if (index == GetSize())
    {
        m_vector.push_back(item);
    }
    else
    {
        m_vector.insert(m_vector.begin() + index, item);
    }
    return true;
}

template <class T>
bool Vector<T>::Add(const T& item)
{
    return Insert(GetSize(), item);
}

/*
template <class T>
bool Vector<T>::Delete(int index)
{
    if (index < 0 || index >= GetSize())
    {
        return false;
    }
    else
    {
        m_vector.erase(m_vector.begin() + index);
        return true;
    }
}
*/

template <class T>
bool Vector<T>::Erase(int index)
{
    if (index < 0 || index >= GetSize())
    {
        return false;
    }
    else
    {
        m_vector.erase(m_vector.begin() + index);
    }
    return true;
}

template <class T>
bool Vector<T>::PopBack()
{
    if (GetSize() == 0)
    {
        return false;
    }
    else
    {
        m_vector.pop_back();
    }
    return true;
}

template <class T>
void Vector<T>::Clear()
{
    m_vector.clear();
}

template <class T>
T& Vector<T>::operator[](int index)
{
    return m_vector[index];
}

template <class T>
const T& Vector<T>::operator[] (int index) const
{
    //handle invalid index through exception handling
    return m_vector[index];
}

template <class T>
int Vector<T>::GetSize() const
{
    return m_vector.size();
}


#endif
