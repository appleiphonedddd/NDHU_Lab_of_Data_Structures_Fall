#include <iostream>
#include <string>
using namespace std;

enum Color
{
    RED,
    BLACK
};

struct Node
{
    string data;
    bool color;
    Node *left;
    Node *right;
    Node *parent;

    Node(string data)
    {
        this->data = data;
        color = RED;
        left = right = parent = NULL;
    }
};

class RedBlackTree
{
private:
    Node *root;

    Node *minValueNode(Node *node)
    {
        Node *current = node;

        while (current && current->left != NULL)
        {
            current = current->left;
        }

        return current;
    }
    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;

        if (y->left != NULL)
        {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == NULL)
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

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;

        if (y->right != NULL)
        {
            y->right->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == NULL)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;
    }

    void insertFixup(Node *z)
    {
        while (z->parent != NULL && z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                Node *y = z->parent->parent->right;
                if (y != NULL && y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                // Same as above with right/left exchanged
            }
        }
        this->root->color = BLACK;
    }

    void deleteFixup(Node *x)
    {
        while (x != this->root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                Node *w = x->parent->right;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }

                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = this->root;
                }
            }
            else
            {
                // Same as above with right/left exchanged
            }
        }
        x->color = BLACK;
    }

    string serialize(Node *root)
    {
        if (root == NULL)
        {
            return "";
        }
        string s = serialize(root->left);
        s += root->data + ",";
        s += serialize(root->right);
        return s;
    }

public:
    RedBlackTree()
    {
        root = NULL;
    }

    void insert(string data)
    {
        Node *z = new Node(data);
        Node *y = NULL;
        Node *x = this->root;

        while (x != NULL)
        {
            y = x;
            if (z->data < x->data)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == NULL)
        {
            this->root = z;
        }
        else if (z->data < y->data)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }

        z->left = z->right = NULL;
        z->color = RED;
        insertFixup(z);
    }

    void deleteNode(string data)
    {
        deleteUtil(this->root, data);
    }

    Node *deleteUtil(Node *root, string data)
    {
        if (root == NULL)
            return root;

        if (data < root->data)
        {
            root->left = deleteUtil(root->left, data);
        }
        else if (data > root->data)
        {
            root->right = deleteUtil(root->right, data);
        }
        else
        {
            if (root->left == NULL || root->right == NULL)
            {
                Node *temp = root->left ? root->left : root->right;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                {
                    *root = *temp;
                }

                free(temp);
            }
            else
            {
                Node *temp = minValueNode(root->right);
                /* Node *minValueNode(Node * node)
                 {
                     Node *current = node;

                     while (current->left != NULL)
                     {
                         current = current->left;
                     }

                     return current;
                 }*/
                root->data = temp->data;
                root->right = deleteUtil(root->right, temp->data);
                

            }
        }

        if (root != NULL)
        {
            deleteFixup(root);
        }

        return root;
    }

    string serialize()
    {
        return serialize(root);
    }
};

int main()
{
    RedBlackTree tree;
    string input;
    while (cin >> input)
    {
        if (input == "insert")
        {
            string data;
            cin >> data;
            tree.insert(data);
        }
        else if (input == "delete")
        {
            string data;
            cin >> data;
            tree.deleteNode(data);
        }
        cout << tree.serialize() << "\n";
    }
    return 0;
}