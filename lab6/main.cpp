#include <iostream>
#include <bitset>

using namespace std;

const int SET_SIZE = 100;

class Set
{
public:
    bitset<SET_SIZE> setBits; // A collection whose elements range from 0 to 99

    // This method attempts to add an element to the collection.
    bool addElement(int e)
    {
        if (e < 0 || e >= SET_SIZE)
        {
            return false; // Invalid value
        }
        setBits.set(e); // Set the bit at index e to 1
        return true;
    }

    // This method computes the union of two sets (the current set and set b).
    Set *unions(Set *b)
    {
        Set *c = new Set();
        c->setBits = this->setBits | b->setBits; // Union operation using bitwise OR
        return c;
    }

    // This method computes the intersection of two sets (the current set and set b).
    Set *intersection(Set *b)
    {
        Set *c = new Set();
        c->setBits = this->setBits & b->setBits; // Intersection operation using bitwise AND
        return c;
    }

    // This method checks whether two collections are equal.
    bool equivalent(Set *b)
    {
        return this->setBits == b->setBits; // Equality check
    }

    void listAll()
    {
        for (int i = 0; i < SET_SIZE; i++)
        {
            if (setBits[i])
            {
                cout << i << " ";
            }
        }
        cout << endl;
    }
};

int main()
{
    Set *a = new Set();
    Set *b = new Set();
    Set *c;

    a->addElement(1);
    a->addElement(2);
    a->addElement(3);
    b->addElement(3);
    b->addElement(4);
    b->addElement(5);

    c = a->unions(b);
    c->listAll();

    c = a->intersection(b);
    c->listAll();

    if (a->equivalent(b) == 0)
        cout << "Not equivalent.\n";
    else
        cout << "Equivalent!\n";

    delete a;
    delete b;
    delete c;

    return 0;
}
