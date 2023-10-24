#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Tree
{
public:
    Tree()
    {
        int j, k;
        for (j = 0; j < 20; j++)
            for (k = 0; k < 4; k++)
                root[j][k] = -1;
    }
    int insert(int node)
    {
        int f = 0, index = 0;
        while (root[index][0] != -1)
            index++;
        if (index >= 20)
            return -1;    // Tree is full
        if (index == 0)
        {
            /**
             * new node is root
            **/
            root[0][0] = 1;
            root[0][1] = node;
            return 1;
        }
        else
        {
            /**
             * new node find in empty place of tree
            **/
            root[index][0] = 1;
            root[index][1] = node;
            while (1)
            {
                if (root[f][1] < node)
                {
                    /**
                     * if the value of the new node is greater than the value of the current node
                     * move to the right child node
                     */
                    if (root[f][3] == -1)
                    {
                        root[f][3] = index;
                        return 1;
                    }
                    else
                    {
                        f = root[f][3];
                    }
                }
                else
                {
                    /**
                     * move to the left child node
                     */
                    if (root[f][2] == -1)
                    {
                        root[f][2] = index;
                        return 1;
                    }
                    else
                    {
                        f = root[f][2];
                    }
                }
            }
        }
    }
    void inorder(int index)
    {
        if (index == -1 || root[index][0] == -1)
            return;

        inorder(root[index][2]);
        cout << root[index][1] << " ";
        inorder(root[index][3]);
    }
    void preorder(int index)
    {
        if (index == -1 || root[index][0] == -1)
            return;
        cout << root[index][1] << " ";
        preorder(root[index][2]);
        preorder(root[index][3]);
    }
    void postorder(int index)
    {
        if (index == -1 || root[index][0] == -1)
            return;

        postorder(root[index][2]);
        postorder(root[index][3]);
        cout << root[index][1] << " ";
    }
    void levelorder()
    {
        int queue[20], front = 0, rear = 0;
        if (root[0][0] != -1)
        {
            queue[rear++] = 0;
        }

        while (front != rear)
        {
            int current = queue[front++];
            cout << root[current][1] << " ";

            if (root[current][2] != -1)
                queue[rear++] = root[current][2];
            if (root[current][3] != -1)
                queue[rear++] = root[current][3];
        }
    }

private:
    int root[20][4];
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
    tree->inorder(0);
    cout << "\n";
    tree->preorder(0);
    cout << "\n";
    tree->postorder(0);
    cout << "\n";
    tree->levelorder();
    cout << "\n";
}