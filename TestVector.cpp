#include <iostream>
#include "Vector.h"
#include "Date.h"

using std::cout;
using std::endl;

template <class T>
void PrintVector(const Vector<T>& vec)
{
    std::cout << "-----------------------------" << std::endl;
    for (int i = 0; i < vec.GetSize(); i++)
    {
        std::cout << vec[i] << std::endl;
    }
}

void TestStringVector()
{
    std::cout << "\n Testing Vector<std::string> " << std::endl;

    Vector<std::string> names;
    names.Insert(0, "Jon");
    names.Insert(1, "Mary");
    names.Insert(0, "King");
    names.Insert(2, "Kong");

    PrintVector(names);
}

void TestIntVector()
{
    std::cout << "\n Testing Vector<int> " << std::endl;

    Vector<int> numbers(6); //6 default items, zeros in output is expected
    numbers.Insert(6, 999);
    numbers.Insert(1, 777);

    PrintVector(numbers);
}

void TestFloatVector()
{
    std::cout << "\n--- Testing Vector<float> ---" << std::endl;

    Vector<float> values;
    values.Add(1.5f);
    values.Add(2.75f);
    values.Insert(1, 9.5f);

    std::cout << "After Add and Insert:" << std::endl;
    PrintVector(values);

    values.Erase(2);
    std::cout << "After Erase index 2:" << std::endl;
    PrintVector(values);

    values.PopBack();
    std::cout << "After PopBack:" << std::endl;
    PrintVector(values);
}

void TestAddErasePopBack()
{
    std::cout << "\n Testing Add / Erase / PopBack " << std::endl;

    Vector<int> values;
    values.Add(10);
    values.Add(20);
    values.Add(30);

    std::cout << "After Add:" << std::endl;
    PrintVector(values);

    values.Erase(1);
    std::cout << "After Erase index 1:" << std::endl;
    PrintVector(values);

    values.PopBack();
    std::cout << "After PopBack:" << std::endl;
    PrintVector(values);

    values.Clear();
    std::cout << "After Clear, size = " << values.GetSize() << std::endl;
}



int main()
{
    std::cout << "--- VECTOR UNIT TESTING ---" << std::endl;

    TestStringVector();
    TestIntVector();
    TestFloatVector();
    TestAddErasePopBack();

    std::cout << "\n--- ALL TESTS COMPLETED ---" << std::endl;
    return 0;
}
