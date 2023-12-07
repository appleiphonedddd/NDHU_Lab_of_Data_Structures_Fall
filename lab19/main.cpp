#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdio>

using namespace std;

template <class T>
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
        out << (*(n.data));
        return out;
    }
    friend std::ostream &operator<<(std::ostream &out, Node *n)
    {
        out << (*(n->data));
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

template <class T>
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

template <class T>
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
        if (head != NULL)
        {
            head->setPrev(node);
        }
        node->setNext(head);
        head = node;
        if (tail == NULL)
            tail = node;
    }
    void addFromTail(T d)
    {
        ListNode<T> *node = new ListNode<T>(d);
        if (tail != NULL)
        {
            tail->setNext(node);
        }
        node->setPrev(tail);
        tail = node;
        if (head == NULL)
            head = node;
    }
    void addAfter(ListNode<T> *at, T d)
    {
        if (!exist(at))
            return;
        ListNode<T> *node = new ListNode<T>(d);
        if (at->getNext() != NULL)
            at->getNext()->setPrev(node);
        node->setNext(at->getNext());
        at->setNext(node);
        node->setPrev(at);
        if (node->getNext() == NULL)
            tail = node;
    }
    ListNode<T> *removeFromHead()
    {
        ListNode<T> *n = head;
        if (head != NULL)
        {
            head = head->getNext();
            if (head != NULL)
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
        if (tail != NULL)
        {
            tail = tail->getPrev();
            if (tail != NULL)
                tail->setNext(NULL);
            else
                head = NULL;
            n->setPrev(NULL);
        }
        return n;
    }
    ListNode<T> *remove(ListNode<T> *n)
    {
        if (!exist(n))
            return NULL;
        if (n == head)
            return removeFromHead();
        if (n == tail)
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
        while (j != NULL)
        {
            if (j->getData() == d)
                return j;
            j = j->getNext();
        }
        return NULL;
    }
    bool exist(ListNode<T> *n)
    {
        ListNode<T> *j = head;
        while (j != NULL)
        {
            if (j == n)
                return true;
            j = j->getNext();
        }
        return false;
    }
    ListNode<T> &operator[](int i)
    {
        ListNode<T> *j = head;
        int k;
        for (k = 0; k < i && j != NULL; k++)
            j = j->getNext();
        if (j == NULL)
            throw std::invalid_argument("index does not exist.");
        return *j;
    }
    void print() const
    {
        ListNode<T> *j;
        j = head;
        while (j != NULL)
        {
            std::cout << (*j) << " ";
            j = j->getNext();
        }
        std::cout << std::endl;
    }

protected:
    ListNode<T> *head, *tail;
};

template <class T>
class GraphNode : public Node<T>
{
public:
    GraphNode() : Node<T>()
    {
        list = new LinkList<T>();
    }
    GraphNode(T d) : Node<T>(d)
    {
        list = new LinkList<GraphNode<T> *>();
    }
    void addLink(GraphNode<T> *node)
    {
        list->addFromTail(node);
    }
    bool exist(GraphNode<T> *node)
    {
        if (list->exist(node))
            return true;
        return false;
    }
    void remove(GraphNode<T> *node)
    {
    }
    ListNode<GraphNode<T> *> *operator[](int n)
    {
        try
        {
            return &(*list)[n];
        }
        catch (std::invalid_argument e)
        {
            return NULL;
        }
    }

private:
    LinkList<GraphNode<T> *> *list;
};

template <class T>
class Graph
{
public:
    Graph()
    {
        vertex = new LinkList<GraphNode<T> *>();
        count = 0;
    }
    GraphNode<T> *addVertex(T d)
    {
        GraphNode<T> *node = new GraphNode<T>(d);
        vertex->addFromTail(node);
        count++;
        return node;
    }
    void addLink(GraphNode<T> *node1, GraphNode<T> *node2)
    {
        node1->addLink(node2);
        node2->addLink(node1);
    }
    bool isLinked(GraphNode<T> *node1, GraphNode<T> *node2)
    {
        return node1->exist(node2);
    }
    GraphNode<T> *operator[](int n)
    {
        try
        {
            return (*vertex)[n].getData();
        }
        catch (std::invalid_argument e)
        {
            return NULL;
        }
    }
    void adjMatrix()
    {
    }
    void adjList()
    {
    }
    void BFS(GraphNode<T> *node)
    {
        LinkList<GraphNode<T> *> *l = new LinkList<GraphNode<T> *>();
        l->addFromTail(node);
        ListNode<GraphNode<T> *> *cur = l->exist(node);
        while (cur != NULL)
        {
            std::cout << cur << " ";
            ListNode<GraphNode<T> *> *e = (*(cur->getData()))[0];
            while (e != NULL)
            {
                if (l->exist(e->getData()) == NULL)
                    l->addFromTail(e->getData());
                e = e->getNext();
            }
            cur = cur->getNext();
        }
    }
    void DFS(GraphNode<T> *node)
    {
        LinkList<GraphNode<T> *> *l = new LinkList<GraphNode<T> *>();
        l->addFromTail(node);
        ListNode<GraphNode<T> *> *cur = l->exist(node);
        while (cur != NULL)
        {
            std::cout << cur << " ";
            ListNode<GraphNode<T> *> *e = (*(cur->getData()))[0];
            while (e != NULL)
            {
                if (l->exist(e->getData()) == NULL)
                    l->addAfter(cur, e->getData());
                e = e->getNext();
            }
            cur = cur->getNext();
        }
    }

private:
    LinkList<GraphNode<T> *> *vertex;
    int count;
};

int main()
{
    Graph<int> *g = new Graph<int>();
    LinkList<GraphNode<int> *> *node = new LinkList<GraphNode<int> *>();
    int j, k, s, a, b, n;
    scanf("%d", &s);
    srand(s);
    n = rand() % 50;
    for (j = 0; j < n; j++)
        node->addFromTail(g->addVertex(j + 1));
    k = rand() % 100;
    for (j = 0; j < k; j++)
    {
        a = rand() % n;
        b = rand() % n;
        g->addLink(((*node)[a]).getData(), ((*node)[b]).getData());
    }
    g->adjMatrix();
    g->adjList();
    return 0;
}
