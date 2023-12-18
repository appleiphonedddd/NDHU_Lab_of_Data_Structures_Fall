#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdio>

using namespace std;

template<class T>
class Node
{
public:
    Node()
    {
        data = new T;
    }
    Node(T d)
    {
        data = new T;
        (*data) = d;
    }
    Node &operator=(T d)
    {
        (*data) = d;
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &out, Node n)
    {
        out<<(*(n.data));
        return out;
    }
    friend std::ostream &operator<<(std::ostream &out, Node *n)
    {
        out<<(*(n->data));
        return out;
    }
    void setData(T d)
    {
        *data = d;
    }
    T &getData() const
    {
        return *data;
    }
protected:
    T *data;
};

template<class T>
class ListNode : public Node<T>
{
public:
    ListNode() : Node<T>()
    {
        prev = NULL;
        next = NULL;
    }
    ListNode(T d) : Node<T>(d)
    {
        prev = NULL;
        next = NULL;
    }
    ListNode(ListNode *p, ListNode *n) : Node<T>()
    {
        prev = p;
        next = n;
    }
    ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
    {
        prev = p;
        next = n;
    }
    ListNode *getNext() const
    {
        return next;
    }
    ListNode *getPrev() const
    {
        return prev;
    }
    void setNext(ListNode *n)
    {
        next = n;
    }
    void setPrev(ListNode *p)
    {
        prev = p;
    }
    ListNode &operator=(T d)
    {
        this->setData(d);
        return *this;
    }
private:
    ListNode *prev, *next;
};

template<class T>
class LinkList
{
public:
    LinkList()
    {
        head = NULL;
        tail = NULL;
    }
    void addFromHead(T d)
    {
        ListNode<T> *node = new ListNode<T>(d);
        if(head != NULL)
        {
            head->setPrev(node);
        }
        node->setNext(head);
        head = node;
        if(tail == NULL)
            tail = node;
    }
    void addFromTail(T d)
    {
        ListNode<T> *node = new ListNode<T>(d);
        if(tail != NULL)
        {
            tail->setNext(node);
        }
        node->setPrev(tail);
        tail = node;
        if(head == NULL)
            head = node;
    }
    void addAfter(ListNode<T> *at, T d)
    {
        if(!exist(at))
            return;
        ListNode<T> *node = new ListNode<T>(d);
        if(at->getNext() != NULL)
            at->getNext()->setPrev(node);
        node->setNext(at->getNext());
        at->setNext(node);
        node->setPrev(at);
        if(node->getNext() == NULL)
            tail = node;
    }
    ListNode<T> *removeFromHead()
    {
        ListNode<T> *n = head;
        if(head != NULL)
        {
            head = head->getNext();
            if(head != NULL)
                head->setPrev(NULL);
            else
                tail = NULL;
            n->setNext(NULL);
        }
        return n;
    }
    ListNode<T> *removeFromTail()
    {
        ListNode<T> *n = tail;
        if(tail != NULL)
        {
            tail = tail->getPrev();
            if(tail != NULL)
                tail->setNext(NULL);
            else
                head = NULL;
            n->setPrev(NULL);
        }
        return n;
    }
    ListNode<T> *remove(ListNode<T> *n)
    {
        if(!exist(n))
            return NULL;
        if(n == head)
            return removeFromHead();
        if(n == tail)
            return removeFromTail();
        n->getPrev()->setNext(n->getNext());
        n->getNext()->setPrev(n->getPrev());
        n->setNext(NULL);
        n->setPrev(NULL);
        return n;
    }
    ListNode<T> *exist(T d)
    {
        ListNode<T> *j = head;
        while(j != NULL)
        {
            if(j->getData() == d)
                return j;
            j = j->getNext();
        }
        return NULL;
    }
    bool exist(ListNode<T> *n)
    {
        ListNode<T> *j = head;
        while(j != NULL)
        {
            if(j == n)
                return true;
            j = j->getNext();
        }
        return false;
    }
    ListNode<T> &operator[](int i)
    {
        ListNode<T> *j = head;
        int k;
        for(k = 0; k < i && j != NULL; k ++)
            j = j->getNext();
        if(j == NULL)
            throw std::invalid_argument("index does not exist.");
        return *j;
    }
    void print() const
    {
        ListNode<T> *j;
        j = head;
        while(j != NULL)
        {
            std::cout<<(*j)<<" ";
            j = j->getNext();
        }
        std::cout<<std::endl;
    }
protected:
    ListNode<T> *head, *tail;
};

template<class T1, class T2>
class Hash {
public:
    struct Pair
    {
        T1 key;
        T2 value;
    };
    Hash()
    {
    	secondTable = NULL;
    }
    bool insert(Pair *data)
    {
        unsigned int k = HASHfunction(data->key);
        if(table[k] == NULL)
            table[k] = data;
        else
        {
        	if(secondTable == NULL)
            	secondTable = new(nothrow) HASH<T1, T2>();
            if(secondTable == NULL)
                return false;
            secondTable->insert(data);
        }
        return true;
    }
    Pair *search(T1 key)
    {
    }
private:
    Pair *table[100];
    Hash *secondTable;
    unsigned int HASHfunction(T1 k)
    {
        unsigned int size = sizeof(T1);
        char *p = (char *)&k;
        unsigned int value = 0, j;
        for(j = 0;j < size;j ++)
        {
            if(j % 2)
                value ^= *p;
            else
                value += *p;
            p ++;
        }
        return value % 100;
    }
};

int main()
{
    int j;
    Hash<int, string> *hash = new Hash<int, string>();
    for(j = 0;j < 1024;j ++)
    {
        Hash<int, string>::Pair *p = new Hash<int, string>::Pair {j, to_string(j)};
        hash->insert(p);
    }
    for(j = 1000;j < 1100;j ++)
    {
        Hash<int, string>::Pair *p = hash->search(j);
        if(p)
            cout << p->value << endl;
        else
            cout << "miss" << endl;
    }
}
