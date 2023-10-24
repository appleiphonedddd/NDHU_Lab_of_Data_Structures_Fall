#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

class Node
{
public:
    int data;
    Node *left, *right;
};

class Tree
{
public:
    Tree()
    {
        root = NULL;
    }
    void insert(Node *n)
    {
        insert(&root, n);
    }

    void inorder()
    {
        inorder(root);
        cout << endl;
    }

    void preorder()
    {
        preorder(root);
        cout << endl;
    }

    void postorder()
    {
        postorder(root);
        cout << endl;
    }

    void levelorder()
    {
        levelorder(root);
        cout << endl;
    }

private:
    Node *root;

    void inorder(Node *current)
    {
        /**
         If the current node exists:
         
         First, recursively traverse the left subtree
         Then, print the data of the current node
         Lastly, recursively traverse the right subtree
         **/
        if (current)
        {
            inorder(current->left);
            cout << current->data << " ";
            inorder(current->right);
        }
    }

    void preorder(Node *current)
    {
        /**
         If the current node exists:

         First, print the data of the current node
         Then, recursively traverse the left subtree
         Lastly, recursively traverse the right subtree
         **/
        if (current)
        {
            cout << current->data << " ";
            preorder(current->left);
            preorder(current->right);
        }
    }

    void postorder(Node *current)
    {
        /**
         If the current node exists:

         First, recursively traverse the left subtree
         Then, recursively traverse the right subtree
         Lastly, print the data of the current node
         **/
        if (current)
        {
            postorder(current->left);
            postorder(current->right);
            cout << current->data << " ";
        }
    }

    void levelorder(Node *current)
    {
        /**
         If the current node doesn't exist, return immediately
         Otherwise, establish a queue and enqueue the current node

         As long as the queue is not empty, do the following:
         Dequeue the front node from the queue
         Print the data of that node
         If the node has a left child, enqueue it
         If the node has a right child, enqueue it
         **/
        if (!current)
            return;

        queue<Node *> q;
        q.push(current);

        while (!q.empty())
        {
            Node *current = q.front(); // retrieve the node at the front of the queue
            q.pop();
            cout << current->data << " ";

            if (current->left != NULL)
            {
                q.push(current->left);
            }
            if (current->right != NULL)
            {
                q.push(current->right);
            }
        }
    }

    void insert(Node **r, Node *n)
    {
        if (*r == NULL)
            *r = n;
        else if (n->data > (*r)->data)
            insert(&((*r)->right), n);
        else
            insert(&((*r)->left), n);
    }
};

int main()
{
    Tree *tree = new Tree();
    Node *node;

    srand(time(NULL));

    for (int j = 0; j < 10; j++)
    {
        node = new Node();
        node->data = rand() % 100; // Modding by 100 for easier visibility
        node->left = NULL;
        node->right = NULL;
        tree->insert(node);
    }

    tree->inorder();
    tree->preorder();
    tree->postorder();
    tree->levelorder();

    delete tree; // Properly delete the tree
    return 0;
}
