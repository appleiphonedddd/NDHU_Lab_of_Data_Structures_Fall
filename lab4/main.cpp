#include <iostream>
#include <cstring>

#define SIZE 100

using namespace std;

class Queue
{
public:
    Queue() : top(-1), bot(-1) {} // Initialize to -1

    bool isFull()
    {
        return ((bot + 1) % SIZE == top);
    }

    bool isEmpty()
    {
        return (top == -1);
    }

    bool enqueue(int data)
    {
        if (isFull())
        {
            return false;
        }
        else
        {
            if (isEmpty())
            {
                top = bot = 0;
            }
            else
            {
                bot = (bot + 1) % SIZE;
            }
            this->data[bot] = data;
            return true;
        }
    }

    int *dequeue()
    {
        if (isEmpty())
        {
            return NULL;
        }
        else
        {
            int *retValue = &data[top];
            if (top == bot)
            {
                top = bot = -1; // Reset if only one element
            }
            else
            {
                top = (top + 1) % SIZE;
            }
            return retValue;
        }
    }

private:
    int data[SIZE];
    int top, bot;
};

int main()
{
    int data, *temp;
    char command[50];
    Queue *queue = new Queue();
    while (1)
    {
        cin >> command;
        if (strcmp(command, "exit") == 0)
        {
            break;
        }
        else if (strcmp(command, "enqueue") == 0)
        {
            cout << "Please input a integer data:";
            cin >> data;
            if (queue->enqueue(data))
            {
                cout << "Successfully enqueue data " << data << " into queue." << endl;
            }
            else
            {
                cout << "Failed to enqueue data into queue." << endl;
            }
        }
        else if (strcmp(command, "dequeue") == 0)
        {
            temp = queue->dequeue();
            if (temp == NULL)
            {
                cout << "Failed to dequeue a data from queue.\n";
            }
            else
            {
                cout << "Dequeue data " << *temp << " from queue." << endl;
            }
        }
    }
    delete queue; // Don't forget to delete the dynamically allocated memory
    return 0;
}
