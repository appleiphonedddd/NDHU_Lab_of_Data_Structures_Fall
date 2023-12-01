#include <iostream>
#include <vector>
#include <queue>

template <typename T>
class RedBlackTree
{
protected:
    enum State
    {
        Red,
        Black
    };
    struct RedBlackNode
    {
        T data;
        State state;
        RedBlackNode *left, *right, *parent;

        RedBlackNode(const T &data, State state, RedBlackNode *parent)
            : data(data), state(state), left(nullptr), right(nullptr), parent(parent) {}

        size_t height() const
        {
            size_t left_height = left ? left->height() : 0;
            size_t right_height = right ? right->height() : 0;
            return 1 + std::max(left_height, right_height);
        }
        size_t size() const
        {
            size_t left_size = left ? left->size() : 0;
            size_t right_size = right ? right->size() : 0;
            return 1 + left_size + right_size;
        }
    }

    // Helper function for deep copy
    RedBlackNode *copyTree(RedBlackNode *node, RedBlackNode *parent = nullptr)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        RedBlackNode *newNode = new RedBlackNode(node->data, node->state, parent);
        newNode->left = copyTree(node->left, newNode);
        newNode->right = copyTree(node->right, newNode);
        return newNode;
    }

    // Helper function for tree destruction
    void destroyTree(RedBlackNode *node)
    {
        if (node)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void insertFixup(RedBlackNode *node)
    {
        while (node != root && node->parent->state == Red)
        {
            if (node->parent == node->parent->parent->left)
            {
                RedBlackNode *uncle = node->parent->parent->right;
                if (uncle && uncle->state == Red)
                {
                    node->parent->state = Black;
                    uncle->state = Black;
                    node->parent->parent->state = Red;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->right)
                    {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->state = Black;
                    node->parent->parent->state = Red;
                    rotateRight(node->parent->parent);
                }
            }
            else
            {
                // Mirror case: node->parent is right child
                // Implement similarly as above, with 'left' and 'right' swapped
            }
        }
        root->state = Black;
    }
    void removeFixup(RedBlackNode *node)
    {
        while (node != root && node->state == Black)
        {
            if (node == node->parent->left)
            {
                RedBlackNode *sibling = node->parent->right;
                // Handle cases when sibling is red, sibling's children are black, etc.
                // Similar to insertFixup, with additional cases
            }
            else
            {
                // Mirror case: node is right child
            }
        }
        node->state = Black;
    }
    RedBlackNode *findNode(const T &val)
    {
        RedBlackNode *current = root;
        while (current != nullptr)
        {
            if (val < current->data)
                current = current->left;
            else if (val > current->data)
                current = current->right;
            else
                return current; // Node found
        }
        return nullptr; // Node not found
    }
    void transplant(RedBlackNode *u, RedBlackNode *v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v != nullptr)
            v->parent = u->parent;
    }
    RedBlackNode *minimum(RedBlackNode *node)
    {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
    RedBlackNode *maximum(RedBlackNode *node)
    {
        while (node->right != nullptr)
            node = node->right;
        return node;
    }

    void rotateLeft(RedBlackNode *x)
    {
        RedBlackNode *y = x->right; // Set y.
        x->right = y->left;         // Turn y's left subtree into x's right subtree.
        if (y->left != nullptr)
        {
            y->left->parent = x;
        }
        y->parent = x->parent; // Link x's parent to y.

        if (x->parent == nullptr) // If x is the root.
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->left = x; // Put x on y's left.
        x->parent = y;
    }

    void rotateRight(RedBlackNode *y)
    {
        RedBlackNode *x = y->left; // Set x.
        y->left = x->right;        // Turn x's right subtree into y's left subtree.
        if (x->right != nullptr)
        {
            x->right->parent = y;
        }
        x->parent = y->parent; // Link y's parent to x.

        if (y->parent == nullptr) // If y is the root.
        {
            this->root = x;
        }
        else if (y == y->parent->right)
        {
            y->parent->right = x;
        }
        else
        {
            y->parent->left = x;
        }

        x->right = y; // Put y on x's right.
        y->parent = x;
    }

    size_t heightHelper(const RedBlackNode *node) const
    {
        if (node == nullptr)
            return 0;

        size_t leftHeight = heightHelper(node->left);
        size_t rightHeight = heightHelper(node->right);

        return 1 + std::max(leftHeight, rightHeight);
    }
    void inOrderHelper(RedBlackNode *node, std::vector<T> &result) const
    {
        if (node != nullptr)
        {
            inOrderHelper(node->left, result);
            result.push_back(node->data);
            inOrderHelper(node->right, result);
        }
    }

    // Helper function for level-order traversal
    void levelOrderHelper(std::vector<T> &result) const
    {
        if (root == nullptr)
            return;

        std::queue<RedBlackNode *> nodesQueue;
        nodesQueue.push(root);

        while (!nodesQueue.empty())
        {
            RedBlackNode *currentNode = nodesQueue.front();
            nodesQueue.pop();

            result.push_back(currentNode->data);

            if (currentNode->left != nullptr)
                nodesQueue.push(currentNode->left);

            if (currentNode->right != nullptr)
                nodesQueue.push(currentNode->right);
        }
    };

public: // constructors, destructors
    RedBlackTree()
    {
        root = nullptr;
    }
    RedBlackTree(const RedBlackTree &srcTree)
    {
        root = copytree(srcTree.root);
    }
    ~RedBlackTree()
    {
        deletetree(root);
    }

public: // methods
    void insert(const T &val)
    {
        RedBlackNode *newNode = new RedBlackNode(val, Red);
        RedBlackNode *y = nullptr;
        RedBlackNode *x = this->root;

        // Binary tree insert
        while (x != nullptr)
        {
            y = x;
            if (newNode->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        newNode->parent = y;
        if (y == nullptr)
            this->root = newNode;
        else if (newNode->data < y->data)
            y->left = newNode;
        else
            y->right = newNode;

        // Fix up the red-black tree properties
        insertFixup(newNode);
    }
    void remove(const T &val)
    {
        RedBlackNode *z = findNode(val);
        if (z == nullptr)
            return; // Node not found

        RedBlackNode *y = z, *x;
        State originalYColor = y->state;

        if (z->left == nullptr)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            originalYColor = y->state;
            x = y->right;

            if (y->parent == z)
                x->parent = y;
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->state = z->state;
        }

        if (originalYColor == Black)
            removeFixup(x);

        delete z;
    }
    bool exists(const T &val) const
    {
        RedBlackNode *current = root;
        while (current != nullptr)
        {
            if (val == current->data)
                return true;
            else if (val < current->data)
                current = current->left;
            else
                current = current->right;
        }
        return false;
    }
    size_t height() const
    {
        return heightHelper(root);
    }
    size_t size() const
    {
        return root ? root->size() : 0;
    }
    std::vector<T> inOrder() const
    {
        std::vector<T> result;
        inOrderHelper(root, result);
        return result;
    }
    std::vector<T> levelOrder() const
    {
        std::vector<T> result;
        levelOrderHelper(result);
        return result;
    }

protected:
    RedBlackNode *root;
};

template <typename T>
void sortByBST(vector<T> &arr)
{
    RedBlackTree<T> tree;
    for (auto data : arr)
        tree.insert(data);
    arr = tree.inOrder();
};
