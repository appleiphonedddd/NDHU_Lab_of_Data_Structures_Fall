#include <iostream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class Node
{
    public:
        int cp;    // value in backpack
        double up; // upper bound
        int rw;    // remaining weight
        int id;    // item id 
        bool x[N];
        Node() {}

        Node(int _cp, double _up, int _rw, int _id)
        {
            cp = _cp;
            up = _up;
            rw = _rw;
            id = _id;
            memset(x, 0, sizeof(x));
        }
        bool operator<(const Node &other) const
        {
            return this->up < other.up;
        
        }
};

template <class T>
class BFS : public priority_queue<Node>
{
    public:

    struct Goods
    {
        int weight;
        int value;

    }good[N];

    struct object
    {
        int id;
        double d;

    }S[N];

    bool cmp(object a1, object a2)
    {
        return a1.d > a2.d;
    }

    double Bound(Node t_node)
    {
        double max_value = t_node.cp;
        int t = t_node.id;
        double left = t_node.rw;

        while(t <= n && w[t] <= left)
        {
            max_value += v[t];
            left-=w[t++];
        }

        if(t <= n)
        {
            max_value += double(v[t]/w[t]*left);
        }
        return max_value;
    }

    int prior_bfs()
    {
        int t, tcp, trw;
        double tup;
        priority_queue<Node> q;
        q.push(Node(0, sumv,w,1));

        while(!q.empty())
        {
            Node live_node, lchild, rchild;
            live_node = q.top();
            q.pop();
            t = live_node.id;

            if(t > n || live_node.rw == 0)
            {
                if(live_node.cp >= bestp)
                {
                    for(int i = 1; i <= n; i++)
                    {
                        bestx[i] = live_node.x[i];
                    }
                    bestp = live_node.cp;
                }
                continue;
            }

            if(live_node.up < bestp)
            {
                continue;
            }

            tcp = live_node.cp;
            trw = live_node.rw;
            if(trw >= w[t])
            {
                lchild.cp = tcp + v[t];
                lchild.rw = trw - w[t];
                lchild.id = t + 1;
                tup = Bound(lchild);
                lchild = Node(lchild.cp, tup, lchild.rw, lchild.id);

                for(int i = 1; i <= n; i++)
                {
                    lchild.x[i] = live_node.x[i];
                }

                lchild.x[t] = true;

                if(lchild.cp > bestp)
                {
                    bestp = lchild.cp;
                }
                q.push(lchild);
            }
            rchild.cp = tcp;
            rchild.rw = trw;
            rchild.id = t + 1;
            tup = Bound(rchild);

            if(tup >= bestp)
            {
                rchild = Node(rchild.cp, tup, rchild.rw, rchild.id);

                for(int i = 1; i <= n; i++)
                {
                    rchild.x[i] = live_node.x[i];
                }

                rchild.x[t] = false;
                q.push(rchild);
            }

        }
        return bestp;
    }
};


class Graph
{
private:
    int num_vertex;
    vector<std::list<int>> AdjList;
    int *color, // 0:white, 1:gray, 2:black
        *predecessor,
        *discover,
        *finish;

public:
    Graph() : num_vertex(0){};
    Graph(int N) : num_vertex(N)
    {
        // initialize Adj List
        AdjList.resize(num_vertex);
    };
    void AddEdgeList(int from, int to);
    void BFS(int Start);
    void DFS(int Start);
    void DFSVisit(int vertex, int &time);
};

template <class T>
class DFS: public Graph
{
public:
    color = new int[num_vertex];
};

int main()
{
    int number;
    cin >> number;

    srand(number);

    for(int i = 0; i < number; i++) {
        for(int j = 0; j < number; j++)
        {
            cout << rand() % 2 << " ";
        }
        cout << endl;
    }

    return 0;
}