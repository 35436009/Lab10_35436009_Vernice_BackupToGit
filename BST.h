#ifndef BST_H
#define BST_H

#include <iostream>

/**
 * @class Node
 * @brief Represents a node in the binary search tree.
 * Stores: data, left, right
 *
 * @author Vernice Foong
 * @version 05
 *
 * @param T Type of the data stored in the node.
 */
template <class T>
class Node
{
public:
    T data;
    Node<T>* left;
    Node<T>* right;

    /**
     * @brief Parameterized constructor.
     * @param Value to store in the node.
     */
    Node(T value);
};

/**
 * @class BST
 * @brief Represents a binary search tree.
 *
 * The BST stores data in sorted order and uses recursive routines
 * for insertion, search, deletion, and traversal.
 *
 * @param T Type of the data stored in the tree.
 */
template <class T>
class BST
{
private:
    Node<T>* root;

    /**
     * @brief Helper for Insert function.
     * @param node Current subtree root.
     * @param value Value to insert.
     * @param inserted Set to true if insertion succeeds.
     * @return The updated subtree root.
     */
    Node<T>* Insert(Node<T>* node, T value, bool& inserted);

    /**
     * @brief Helper for Search function.
     * @param node Current subtree root.
     * @param value Value to search for.
     * @return True if value is found, false otherwise.
     */
    bool Search(Node<T>* node, T value) const;

    /**
     * @brief Helper for Delete function.
     * @param node Current subtree root.
     * @param value Value to delete.
     * @param deleted Set to true if deletion succeeds.
     * @return The updated subtree root.
     */
    Node<T>* Delete(Node<T>* node, T value, bool& deleted);

    /**
     * @brief Finds the smallest node in a subtree.
     * @param node Subtree root.
     * @return Pointer to the node with the smallest value.
     */
    Node<T>* FindMin(Node<T>* node) const;

    /**
     * @brief Helper for inorder traversal.
     * @param node Current subtree root.
     * @param visit Function callback.
     */
    void Inorder(Node<T>* node, void (*visit)(const T&)) const;

    /**
     * @brief Helper for preorder traversal.
     * @param node Current subtree root.
     * @param visit Function callback.
     */
    void Preorder(Node<T>* node, void (*visit)(const T&)) const;

    /**
     * @brief Helper for postorder traversal.
     * @param node Current subtree root.
     * @param visit Function callback.
     */
    void Postorder(Node<T>* node, void (*visit)(const T&)) const;

    /**
     * @brief Recursively deletes all nodes in the subtree.
     * @param node Current subtree root.
     */
    void DeleteTree(Node<T>* node);

    /**
     * @brief Recursively copies a subtree.
     * @param node Subtree to copy.
     * @return Pointer to the copied subtree.
     */
    Node<T>* CopyTree(Node<T>* node) const;

public:
    /**
     * @brief Default constructor.
     */
    BST();

    /**
     * @brief Copy constructor.
     * @param other The BST to copy from.
     */
    BST(const BST<T>& other);

    /**
     * @brief Destructor.
     */
    ~BST();

    /**
     * @brief Assignment operator.
     * @param other The BST to assign from.
     * @return Reference to this BST.
     */
    BST<T>& operator=(const BST<T>& other);

    /**
     * @brief Inserts a value into the tree.
     * @return True if inserted, false if already exists.
     */
    bool Insert(T value);

    /**
     * @brief Searches for a value in the tree.
     * @return True if found, false otherwise.
     */
    bool Search(T value) const;

    /**
     * @brief Deletes a value from the tree.
     * @return True if deleted, false if not found.
     */
    bool Delete(T value);

    /**
     * @brief Performs inorder traversal using a callback.
     */
    void Inorder(void (*visit)(const T&)) const;

    /**
     * @brief Performs preorder traversal using a callback.
     */
    void Preorder(void (*visit)(const T&)) const;

    /**
     * @brief Performs postorder traversal using a callback.
     */
    void Postorder(void (*visit)(const T&)) const;

    /**
     * @brief Deletes the entire tree.
     */
    void DeleteTree();
};

// Node implementation
template <class T>
Node<T>::Node(T value)
{
    data = value;
    left = NULL;
    right = NULL;
}

// BST implementation
template <class T>
BST<T>::BST()
{
    root = NULL;
}

template <class T>
BST<T>::BST(const BST<T>& other)
{
    root = CopyTree(other.root);
}

template <class T>
BST<T>::~BST()
{
    DeleteTree();
}

template <class T>
BST<T>& BST<T>::operator=(const BST<T>& other)
{
    if (this != &other)
    {
        DeleteTree();
        root = CopyTree(other.root);
    }

    return *this;
}

template <class T>
bool BST<T>::Insert(T value)
{
    bool inserted = false;
    root = Insert(root, value, inserted);
    return inserted;
}

template <class T>
Node<T>* BST<T>::Insert(Node<T>* node, T value, bool& inserted)
{
    if (node == NULL)
    {
        inserted = true;
        return new Node<T>(value);
    }

    if (value < node->data)
    {
        node->left = Insert(node->left, value, inserted);
    }
    else if (value > node->data)
    {
        node->right = Insert(node->right, value, inserted);
    }
    else
    {
        inserted = false;
    }

    return node;
}

template <class T>
bool BST<T>::Search(T value) const
{
    return Search(root, value);
}

template <class T>
bool BST<T>::Search(Node<T>* node, T value) const
{
    if (node == NULL)
    {
        return false;
    }

    if (value == node->data)
    {
        return true;
    }

    if (value < node->data)
    {
        return Search(node->left, value);
    }

    return Search(node->right, value);
}

template <class T>
bool BST<T>::Delete(T value)
{
    bool deleted = false;
    root = Delete(root, value, deleted);
    return deleted;
}

template <class T>
Node<T>* BST<T>::Delete(Node<T>* node, T value, bool& deleted)
{
    if (node == NULL)
    {
        deleted = false;
        return NULL;
    }

    if (value < node->data)
    {
        node->left = Delete(node->left, value, deleted);
    }
    else if (value > node->data)
    {
        node->right = Delete(node->right, value, deleted);
    }
    else
    {
        deleted = true;

        if (node->left == NULL && node->right == NULL)
        {
            delete node;
            return NULL;
        }
        else if (node->left == NULL)
        {
            Node<T>* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL)
        {
            Node<T>* temp = node->left;
            delete node;
            return temp;
        }
        else
        {
            Node<T>* minNode = FindMin(node->right);
            node->data = minNode->data;
            node->right = Delete(node->right, minNode->data, deleted);
        }
    }

    return node;
}

template <class T>
Node<T>* BST<T>::FindMin(Node<T>* node) const
{
    if (node == NULL)
    {
        return NULL;
    }

    while (node->left != NULL)
    {
        node = node->left;
    }

    return node;
}

template <class T>
void BST<T>::Inorder(void (*visit)(const T&)) const
{
    Inorder(root, visit);
}

template <class T>
void BST<T>::Inorder(Node<T>* node, void (*visit)(const T&)) const
{
    if (node == NULL)
    {
        return;
    }

    Inorder(node->left, visit);
    visit(node->data);
    Inorder(node->right, visit);
}

template <class T>
void BST<T>::Preorder(void (*visit)(const T&)) const
{
    Preorder(root, visit);
}

template <class T>
void BST<T>::Preorder(Node<T>* node, void (*visit)(const T&)) const
{
    if (node == NULL)
    {
        return;
    }

    visit(node->data);
    Preorder(node->left, visit);
    Preorder(node->right, visit);
}

template <class T>
void BST<T>::Postorder(void (*visit)(const T&)) const
{
    Postorder(root, visit);
}

template <class T>
void BST<T>::Postorder(Node<T>* node, void (*visit)(const T&)) const
{
    if (node == NULL)
    {
        return;
    }

    Postorder(node->left, visit);
    Postorder(node->right, visit);
    visit(node->data);
}

template <class T>
void BST<T>::DeleteTree()
{
    DeleteTree(root);
    root = NULL;
}

template <class T>
void BST<T>::DeleteTree(Node<T>* node)
{
    if (node == NULL)
    {
        return;
    }

    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
}

template <class T>
Node<T>* BST<T>::CopyTree(Node<T>* node) const
{
    if (node == NULL)
    {
        return NULL;
    }

    Node<T>* newNode = new Node<T>(node->data);
    newNode->left = CopyTree(node->left);
    newNode->right = CopyTree(node->right);
    return newNode;
}

#endif
