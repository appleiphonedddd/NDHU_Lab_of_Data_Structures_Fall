#include <iostream>
#include <algorithm>

template <class T>
class Node
{
public:
    T key;
    Node *left;
    Node *right;
    int height;

    Node(T value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

template <class T>
class AVLTree
{
private:
    Node<T> *root;

    // A utility function to get the height of the tree
    int height(Node<T> *N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    // A utility function to right rotate subtree rooted with y
    Node<T> *rightRotate(Node<T> *y)
    {
        Node<T> *x = y->left;
        Node<T> *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        // Return new root
        return x;
    }

    // A utility function to left rotate subtree rooted with x
    Node<T> *leftRotate(Node<T> *x)
    {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        // Return new root
        return y;
    }

    // Get Balance factor of node N
    int getBalance(Node<T> *N)
    {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    // Recursive function to insert a key in the subtree rooted with node and returns the new root of the subtree.
    Node<T> *insert(Node<T> *node, T key)
    {
        // 1. Perform the normal BST insertion
        if (node == nullptr)
            return (new Node<T>(key));

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else // Equal keys not allowed
            return node;

        // 2. Update height of this ancestor node
        node->height = 1 + std::max(height(node->left), height(node->right));

        // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
        int balance = getBalance(node);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // return the (unchanged) node pointer
        return node;
    }

    // A utility function to do inorder traversal of the tree
    void inorder(Node<T> *root)
    {
        if (root != nullptr)
        {
            inorder(root->left);
            std::cout << root->key << " ";
            inorder(root->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T key)
    {
        root = insert(root, key);
    }

    void inorderTraversal()
    {
        inorder(root);
    }
};

int main()
{
    AVLTree<int> tree;
    srand(0);

    for (int j = 0; j < 20; j++)
    {
        tree.insert(rand() % 100);
        tree.inorderTraversal();
        std::cout << std::endl; // For better readability
    }
}
