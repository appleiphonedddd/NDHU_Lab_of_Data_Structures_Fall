#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
using namespace std;

class Tree
{
public:
    // Make sure array is empty = -1
    Tree()
    {
        int j;
        for (j = 0; j < 2000; j++)
            root[j] = -1;
    }
    void inorder()
    {
        inorder(0);
        cout << endl;
    }
    void preorder()
    {
        preorder(0);
        cout << endl;
    }
    void postorder()
    {
        postorder(0);
        cout << endl;
    }
    void levelorder()
    {
        levelorderTraversal();
        cout << endl;
    }
    void insert(int node)
    {
        int index = 0; // Root starts at 0
        while (index < 2000 && root[index] != -1)
        {
            if (root[index] < node)     // Go right
                index = index * 2 + 2;  
            else                        // Go left
                index = index * 2 + 1;
        }
        root[index] = node;             // Insert new node
    }
    void inorder(int index)
    {
        if (index >= 2000 || root[index] == -1)
        {
            inorder(index * 2 + 1);     // Go left
            cout << root[index] << " "; // Print current node
            inorder(index * 2 + 2);     // Go right
        }
    }
    void preorder(int index)
    {
        if (index >= 2000 || root[index] == -1) return;
        cout << root[index] << " "; // Visit node
        preorder(index * 2 + 1);    // Left subtree
        preorder(index * 2 + 2);    // Right subtree
    }
    void postorder(int index)
    {
        if (index >= 2000 || root[index] == -1)return;
        postorder(index * 2 + 1);   // Left subtree
        postorder(index * 2 + 2);   // Right subtree
        cout << root[index] << " "; // Visit node
    }
    void levelorderTraversal()
    {
        queue<int> q;
        if (root[0] != -1)
            q.push(0); // Start with root

        while (!q.empty())
        {
            int index = q.front();
            q.pop();
            cout << root[index] << " ";

            int left = index * 2 + 1;
            int right = index * 2 + 2;

            if (left < 2000 && root[left] != -1)
                q.push(left);
            if (right < 2000 && root[right] != -1)
                q.push(right);
        }
    }

private:
    int root[2000];
};

int main()
{
    Tree *tree = new Tree();
    int j, node;
    srand(time(NULL));
    for (j = 0; j < 10; j++)
    {
        node = rand();
        tree->insert(node);
    }
    tree->inorder();
    printf("\n");
    tree->preorder();
    printf("\n");
    tree->postorder();
    printf("\n");
    tree->levelorder();
    printf("\n");
}
