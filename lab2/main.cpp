#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
class Memory
{
public:
    static T **allocArray(int m, int n)
    {
        T **temp = new T *[m];
        T *data = new T[m * n];

        for (int i = 0; i < m; i++)
        {
            temp[i] = data + i * n;
        }

        return temp;
    }

    static void deallocArray(T **array)
    {
        delete[] array[0]; // Delete the data
        delete[] array;    // Delete the row pointers
    }
};

int main()
{
    try
    {
        int **array = Memory<int>::allocArray(5, 10);

        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 10; k++)
                array[j][k] = j * 10 + k;

        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                cout << array[j][k] << " ";
            }
            cout << endl;
        }

        Memory<int>::deallocArray(array);
    }
    catch (const std::bad_alloc &e)
    {
        cerr << "Memory allocation failed: " << e.what() << endl;
    }

    return 0;
}
