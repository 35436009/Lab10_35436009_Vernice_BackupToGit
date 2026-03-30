#include "BST.h"
#include "Date.h"
#include <iostream>
#include <string>

void RunDateTreeTest()
{
    BST<Date> dateTree;
    std::string tempStr;

    Date d1(31, 3, 2016);
    Date d2(1, 4, 2016);
    Date d3(15, 2, 2015);
    Date d4(10, 12, 2017);
    Date d5(31, 3, 2016);   // duplicate
    Date d6(2, 1, 2007);
    Date d7(25, 12, 2018);
    Date d8(9, 8, 2014);

    std::cout << "Insert tests\n";
    std::cout << "Insert 31/3/2016: " << dateTree.Insert(d1) << std::endl;
    std::cout << "Insert 1/4/2016: " << dateTree.Insert(d2) << std::endl;
    std::cout << "Insert 15/2/2015: " << dateTree.Insert(d3) << std::endl;
    std::cout << "Insert 10/12/2017: " << dateTree.Insert(d4) << std::endl;
    std::cout << "Insert duplicate 31/3/2016: " << dateTree.Insert(d5) << std::endl;
    std::cout << "Insert 2/1/2007: " << dateTree.Insert(d6) << std::endl;
    std::cout << "Insert 25/12/2018: " << dateTree.Insert(d7) << std::endl;
    std::cout << "Insert 9/8/2014: " << dateTree.Insert(d8) << std::endl;

    std::cout << std::endl;
    std::cout << "Traversal tests" << std::endl;
    std::cout << "In-order: ";
    dateTree.Inorder();
    std::cout << std::endl;

    std::cout << "Pre-order: ";
    dateTree.Preorder();
    std::cout << std::endl;

    std::cout << "Post-order: ";
    dateTree.Postorder();
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Press Enter to continue to search, insert and delete tests...";
    std::getline(std::cin, tempStr);

    std::cout << std::endl;
    std::cout << "Search tests before delete" << std::endl;
    std::cout << "Search 2/1/2007: "
              << dateTree.Search(Date(2, 1, 2007)) << std::endl;
    std::cout << "Search 1/4/2016: "
              << dateTree.Search(Date(1, 4, 2016)) << std::endl;
    std::cout << "Search 25/12/2018: "
              << dateTree.Search(Date(25, 12, 2018)) << std::endl;
    std::cout << "Search 5/5/2020: "
              << dateTree.Search(Date(5, 5, 2020)) << std::endl;
    std::cout << "Search 7/7/2001: "
              << dateTree.Search(Date(7, 7, 2001)) << std::endl;
    std::cout << "Search 30/11/2022: "
              << dateTree.Search(Date(30, 11, 2022)) << std::endl;

    std::cout << std::endl;
    std::cout << "Extra insert test" << std::endl;
    std::cout << "Insert 6/6/2011: "
              << dateTree.Insert(Date(6, 6, 2011)) << std::endl;

    std::cout << std::endl;
    std::cout << "Delete tests" << std::endl;
    std::cout << "Delete 2/1/2007: "
              << dateTree.Delete(Date(2, 1, 2007)) << std::endl;
    std::cout << "Delete 5/5/2020: "
              << dateTree.Delete(Date(5, 5, 2020)) << std::endl;

    std::cout << std::endl;
    std::cout << "Search after delete" << std::endl;
    std::cout << "Search 2/1/2007: "
              << dateTree.Search(Date(2, 1, 2007)) << std::endl;
    std::cout << "Search 1/4/2016: "
              << dateTree.Search(Date(1, 4, 2016)) << std::endl;
    std::cout << "Search 6/6/2011: "
              << dateTree.Search(Date(6, 6, 2011)) << std::endl;

    std::cout << std::endl;
    std::cout << "In-order after delete: ";
    dateTree.Inorder();
    std::cout << std::endl;
}