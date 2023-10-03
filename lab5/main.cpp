#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Node
{
public:
    // Stores data values, pointers to next node and previous node

    int data;
    Node *next;
    Node *pre;
    Node(int val) : data(val), next(NULL), pre(NULL) {}
};

class List
{
public:
    Node *head;
    int size;
    List() : head(NULL), size(0) {}

    // Generate n random numbers and add them to the list
    void generate(int n)
    {
        srand(time(NULL));
        for (int i = 0; i < n; ++i)
        {
            Node *newNode = new Node(rand() % 100); // Assuming max value is 100
            newNode->next = head;
            if (head != NULL)
                head->pre = newNode;
            head = newNode;
            size++;
        }
    }

    // Convert linked list to array
    void toArray(int arr[])
    {
        Node *temp = head;
        for (int i = 0; temp != NULL; ++i, temp = temp->next)
        {
            arr[i] = temp->data;
        }
    }

    // Convert array back to linked list
    void fromArray(int arr[])
    {
        Node *temp = head;
        for (int i = 0; i < size; ++i, temp = temp->next)
        {
            temp->data = arr[i];
        }
    }

    /*
    Bubble Sort:

    1. Start: Set index i to 0.
    2. Loop starts (i < n-1):
        Set index j to 0.
        Inner loop starts (j < n-i-1):
           Comparison: If array elements `arr[j]` are greater than `arr[j+1]`, swap them.
           UPDATE: j = j + 1.
        End of inner loop
        UPDATE: i = i + 1.
    3. End of loop
    4. End: Sorting completed.
    */
    void bubbleSort()
    {
        int *arr = new int[size];
        toArray(arr);
        // index = 0 then
        for (int i = 0; i < size - 1; ++i)
        {
            for (int j = 0; j < size - i - 1; ++j)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
        fromArray(arr);
        delete[] arr;
    }

    /*
    Selection Sort:

    1.Start: Set index i to 0.
    2.Loop starts (i < n-1):
        Set min_idx to i.
        Set index j to i + 1.
        Inner loop starts (j < n):
            Compare: If arr[j] is less than arr[min_idx], update min_idx = j.
            Update: j = j + 1.
        End of inner loop
        Swapping: If min_idx is not equal to i, swap arr[i] and arr[min_idx].
        Update: i = i + 1.
    3.end of loop
    4.End: Sorting completed.
    */

    void selectionSort()
    {
        int *arr = new int[size];
        toArray(arr);
        for (int i = 0; i < size - 1; ++i)
        {
            int min_idx = i;
            for (int j = i + 1; j < size; ++j)
            {
                if (arr[j] < arr[min_idx])
                {
                    min_idx = j;
                }
            }
            swap(arr[min_idx], arr[i]);
        }
        fromArray(arr);
        delete[] arr;
    }

    /*
    Insertion Sort:

    1.Start: Set index i to 1.
    2.Loop starts (i < n):
        Set key to arr[i].
        Set index j to i - 1.
        Inner loop starts (j >= 0 and arr[j] > key):
            Move: arr[j+1] = arr[j].
            Update: j = j - 1.
        End of inner loop
        Insertion: arr[j+1] = key.
        Update: i = i + 1.
    3.end of loop
    4.End: Sorting completed.
    */
    void insertionSort()
    {
        int *arr = new int[size];
        toArray(arr);
        for (int i = 1; i < size; ++i)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
        fromArray(arr);
        delete[] arr;
    }

    void print()
    {
        for (Node *temp = head; temp != NULL; temp = temp->next)
        {
            cout << temp->data << " ";
        }
        cout << endl;
    }
};

int main()
{
    List l;
    l.generate(10);
    l.print();
    l.bubbleSort();
    l.print();
    l.generate(10);
    l.print();
    l.selectionSort();
    l.print();
    l.generate(10);
    l.print();
    l.insertionSort();
    l.print();

    return 0;
}
