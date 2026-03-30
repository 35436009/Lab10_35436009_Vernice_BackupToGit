#include "BST.h"
#include "Date.h"
#include <iostream>

/*
int main()
{
    RunBSTTest();
    return 0;
}
*/

// Callback for traversal
void PrintDate(const Date& d)
{
    std::cout << d << " ";
}

// Pass by value
void TestByValue(BST<Date> tree)
{
    std::cout << "By value inorder: ";
    tree.Inorder(PrintDate);
    std::cout << std::endl;
}

// Pass by const reference
void TestByConstRef(const BST<Date>& tree)
{
    std::cout << "By const ref inorder: ";
    tree.Inorder(PrintDate);
    std::cout << std::endl;
}

// Pass by reference
void TestByRef(BST<Date>& tree)
{
    std::cout << "By ref inorder: ";
    tree.Inorder(PrintDate);
    std::cout << std::endl;
}

// Minimal BST test
void RunBSTTest()
{
    BST<Date> tree;

    Date d1(2, 3, 2015);
    Date d2(5, 4, 2015);
    Date d3(2, 2, 2016);
    Date d4(15, 6, 2015);
    Date d5(10, 1, 2016);

    std::cout << "BST insert tests\n";
    std::cout << "Insert 2/3/2015: " << tree.Insert(d1) << std::endl;
    std::cout << "Insert 5/4/2015: " << tree.Insert(d2) << std::endl;
    std::cout << "Insert 2/2/2016: " << tree.Insert(d3) << std::endl;
    std::cout << "Insert 15/6/2015: " << tree.Insert(d4) << std::endl;
    std::cout << "Insert duplicate 2/3/2015: " << tree.Insert(d1) << std::endl;

    std::cout << "\nSearch tests\n";
    std::cout << "Search 5/4/2015: " << tree.Search(d2) << std::endl;
    std::cout << "Search 1/1/2005: " << tree.Search(Date(1, 1, 2005)) << std::endl;

    std::cout << "\nTraversal test\n";
    std::cout << "Inorder: ";
    tree.Inorder(PrintDate);
    std::cout << std::endl;

    std::cout << "\nDelete test\n";
    std::cout << "Delete 15/6/2015: " << tree.Delete(d4) << std::endl;
    std::cout << "Delete 1/1/2005: " << tree.Delete(Date(1, 1, 2005)) << std::endl;

    std::cout << "\nInorder after delete: ";
    tree.Inorder(PrintDate);
    std::cout << std::endl;

    std::cout << "\nCopy constructor test\n";
    BST<Date> copyTree(tree);
    std::cout << "Copy inorder: ";
    copyTree.Inorder(PrintDate);
    std::cout << std::endl;

    std::cout << "\nAssignment operator test\n";
    BST<Date> assignTree;
    assignTree = tree;
    std::cout << "Assigned inorder: ";
    assignTree.Inorder(PrintDate);
    std::cout << std::endl;

    std::cout << "\nPass-by tests\n";
    TestByValue(tree);
    TestByConstRef(tree);
    TestByRef(tree);
}

