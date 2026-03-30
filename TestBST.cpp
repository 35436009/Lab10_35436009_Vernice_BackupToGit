#include "BST.h"
#include <iostream>

// Prints whether a test passed or failed.
void PrintTestResult(const char* testName, bool passed)
{
    if (passed)
    {
        std::cout << "PASS " << testName << std::endl;
    }
    else
    {
        std::cout << "FAIL " << testName << std::endl;
    }
}

// Tests whether a new tree is empty.
void TestEmptyTree()
{
    std::cout << "\n--- Test: Empty Tree ---" << std::endl;

    BST<int> tree;

    bool passed = true;

    passed = passed && (tree.Search(10) == false);

    std::cout << "In-order traversal of empty tree: ";
    tree.Inorder();
    std::cout << std::endl;

    std::cout << "Pre-order traversal of empty tree: ";
    tree.Preorder();
    std::cout << std::endl;

    std::cout << "Post-order traversal of empty tree: ";
    tree.Postorder();
    std::cout << std::endl;

    PrintTestResult("Empty tree search", passed);
}

// Tests inserting one value.
void TestSingleInsert()
{
    std::cout << "\n--- Test: Single Insert ---" << std::endl;

    BST<int> tree;

    bool inserted = tree.Insert(25);
    bool found = tree.Search(25);

    std::cout << "In-order: ";
    tree.Inorder();
    std::cout << std::endl;

    PrintTestResult("Insert(25) should return true", inserted == true);
    PrintTestResult("Search(25) should return true", found == true);
}

// Tests inserting several values.
void TestMultipleInsert()
{
    std::cout << "\n--- Test: Multiple Insert ---" << std::endl;

    BST<int> tree;

    tree.Insert(50);
    tree.Insert(25);
    tree.Insert(75);
    tree.Insert(10);
    tree.Insert(30);
    tree.Insert(60);
    tree.Insert(90);

    std::cout << "Expected In-order: 10 25 30 50 60 75 90" << std::endl;
    std::cout << "Actual   In-order: ";
    tree.Inorder();
    std::cout << std::endl;

    std::cout << "Expected Pre-order: 50 25 10 30 75 60 90" << std::endl;
    std::cout << "Actual   Pre-order: ";
    tree.Preorder();
    std::cout << std::endl;

    std::cout << "Expected Post-order: 10 30 25 60 90 75 50" << std::endl;
    std::cout << "Actual   Post-order: ";
    tree.Postorder();
    std::cout << std::endl;

    bool passed = true;
    passed = passed && tree.Search(50);
    passed = passed && tree.Search(25);
    passed = passed && tree.Search(75);
    passed = passed && tree.Search(10);
    passed = passed && tree.Search(30);
    passed = passed && tree.Search(60);
    passed = passed && tree.Search(90);

    PrintTestResult("Multiple insert and search", passed);
}

// Tests duplicate insertion.
void TestDuplicateInsert()
{
    std::cout << "\n--- Test: Duplicate Insert ---" << std::endl;

    BST<int> tree;

    bool firstInsert = tree.Insert(25);
    bool secondInsert = tree.Insert(25);

    std::cout << "Tree contents: ";
    tree.Inorder();
    std::cout << std::endl;

    PrintTestResult("First insert should return true", firstInsert == true);
    PrintTestResult("Second insert of duplicate should return false", secondInsert == false);
}

// Tests searching for existing and missing values.
void TestSearch()
{
    std::cout << "\n--- Test: Search ---" << std::endl;

    BST<int> tree;

    tree.Insert(50);
    tree.Insert(25);
    tree.Insert(75);
    tree.Insert(10);
    tree.Insert(30);

    bool found1 = tree.Search(50);
    bool found2 = tree.Search(10);
    bool found3 = tree.Search(999);

    PrintTestResult("Search existing root value", found1 == true);
    PrintTestResult("Search existing leaf value", found2 == true);
    PrintTestResult("Search missing value", found3 == false);
}

// Tests deleting a leaf node.
void TestDeleteLeaf()
{
    std::cout << "\n--- Test: Delete Leaf Node ---" << std::endl;

    BST<int> tree;

    tree.Insert(50);
    tree.Insert(25);
    tree.Insert(75);
    tree.Insert(10);
    tree.Insert(30);

    bool deleted = tree.Delete(10);
    bool found = tree.Search(10);

    std::cout << "Expected In-order after deleting 10: 25 30 50 75" << std::endl;
    std::cout << "Actual   In-order: ";
    tree.Inorder();
    std::cout << std::endl;

    PrintTestResult("Delete leaf node should return true", deleted == true);
    PrintTestResult("Deleted leaf node should not be found", found == false);
}

// Tests deleting a node with one child.
void TestDeleteOneChild()
{
    std::cout << "\n--- Test: Delete Node With One Child ---" << std::endl;

    BST<int> tree;

    tree.Insert(50);
    tree.Insert(25);
    tree.Insert(75);
    tree.Insert(10);

    bool deleted = tree.Delete(25);
    bool found = tree.Search(25);

    std::cout << "Tree after deleting 25: ";
    tree.Inorder();
    std::cout << std::endl;

    PrintTestResult("Delete node with one child should return true", deleted == true);
    PrintTestResult("Deleted node should not be found", found == false);
}

// Tests deleting a node with two children.
void TestDeleteTwoChildren()
{
    std::cout << "\n--- Test: Delete Node With Two Children ---" << std::endl;

    BST<int> tree;

    tree.Insert(50);
    tree.Insert(25);
    tree.Insert(75);
    tree.Insert(10);
    tree.Insert(30);
    tree.Insert(60);
    tree.Insert(90);

    bool deleted = tree.Delete(50);
    bool found = tree.Search(50);

    std::cout << "Tree after deleting 50: ";
    tree.Inorder();
    std::cout << std::endl;

    PrintTestResult("Delete node with two children should return true", deleted == true);
    PrintTestResult("Deleted node should not be found", found == false);
}

// Tests deleting all nodes from the tree.
void TestDeleteTree()
{
    std::cout << "\n--- Test: DeleteTree ---" << std::endl;

    BST<int> tree;

    tree.Insert(50);
    tree.Insert(25);
    tree.Insert(75);
    tree.Insert(10);
    tree.Insert(30);

    tree.DeleteTree();

    bool passed = true;
    passed = passed && (tree.Search(50) == false);
    passed = passed && (tree.Search(25) == false);
    passed = passed && (tree.Search(10) == false);

    std::cout << "In-order after DeleteTree: ";
    tree.Inorder();
    std::cout << std::endl;

    PrintTestResult("DeleteTree should make tree empty", passed);
}

// Tests the copy constructor.
void TestCopyConstructor()
{
    std::cout << "\n--- Test: Copy Constructor ---" << std::endl;

    BST<int> originalTree;
    originalTree.Insert(50);
    originalTree.Insert(25);
    originalTree.Insert(75);

    BST<int> copiedTree(originalTree);

    bool beforeChange = true;
    beforeChange = beforeChange && copiedTree.Search(50);
    beforeChange = beforeChange && copiedTree.Search(25);
    beforeChange = beforeChange && copiedTree.Search(75);

    originalTree.Delete(25);

    bool copyStillHas25 = copiedTree.Search(25);

    std::cout << "Original tree after deleting 25: ";
    originalTree.Inorder();
    std::cout << std::endl;

    std::cout << "Copied tree should still contain 25: ";
    copiedTree.Inorder();
    std::cout << std::endl;

    PrintTestResult("Copied tree initially matches original", beforeChange);
    PrintTestResult("Copied tree is independent after copy constructor", copyStillHas25 == true);
}

// Runs all BST tests.
void RunAllBSTTests()
{
    std::cout << "==============================" << std::endl;
    std::cout << "Running BST Tests" << std::endl;
    std::cout << "==============================" << std::endl;

    TestEmptyTree();
    TestSingleInsert();
    TestMultipleInsert();
    TestDuplicateInsert();
    TestSearch();
    TestDeleteLeaf();
    TestDeleteOneChild();
    TestDeleteTwoChildren();
    TestDeleteTree();
    TestCopyConstructor();

    std::cout << "\n==============================" << std::endl;
    std::cout << "Finished BST Tests" << std::endl;
    std::cout << "==============================" << std::endl;
}