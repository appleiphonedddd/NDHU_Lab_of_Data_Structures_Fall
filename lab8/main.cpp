#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid
{
public:
    Grid()
    {
        Grid(0);
    }
    Grid(int s)
    {
        state = s;
        dir[UP] = NULL;
        dir[DOWN] = NULL;
        dir[LEFT] = NULL;
        dir[RIGHT] = NULL;
    }
    Grid *getDir(int d) { return dir[d]; }
    int getState() { return state; }
    void setDir(int d, Grid *g) { dir[d] = g; }
    void setState(int s) { state = s; }

private:
    Grid *dir[4];
    int state;
};

struct List
{
public:
    List()
    {
        top = 0;
    }
    /*
    Insert an element from top
    */
    void addElement(Grid *g)
    {
        if (top < SIZE * SIZE)
            data[top++] = g;
        else
            cout << "List is full\n";
    }
    /*
    remove an element from top and return a pointer point to the element.
    If list is empty, return NULL.
    */
    Grid *removeElement()
    {
        if (top == 0)
        {
            cout << "List is empty\n";
            return NULL;
        }
        else
            return data[--top];
    }
    void printPath()
    {
        int j;
        for (j = 1; j < top; j++)
        {
            if (data[j] == data[j - 1]->getDir(UP))
            {
                cout << "UP\n";
            }
            else if (data[j] == data[j - 1]->getDir(DOWN))
            {
                cout << "DOWN\n";
            }
            else if (data[j] == data[j - 1]->getDir(LEFT))
            {
                cout << "LEFT\n";
            }
            else if (data[j] == data[j - 1]->getDir(RIGHT))
            {
                cout << "RIGHT\n";
            }
        }
    }

private:
    Grid *data[SIZE * SIZE];
    int top;
};

class Maze
{
public:
    Maze()
    {
        initMaze(SIZE);
    }
    /*
    function initMaze
    Alocate a 2-D link list with s * s sizes as the map of maze.
    Inside the maze enery gird with state 0 represent empty space and 1 represent wall.
    The gird in left top is start point and right bottom is finish point.
    Randomly generate 20% wall in the maze.
    Make sure start point and finish point are 0

    動態配置一個二維的鏈結串列，大小是 s * s，用這個鏈結串列表示迷宮的地圖
    節點中 0 的值表示可以移動的空間， 1 表示牆壁
    左上角的位置表示起點，右下角的位置表示終點
    請在迷宮中加入 20% 的牆壁
    然後確定起點跟終點都是可以移動的位置
    */
    void initMaze(int s)
    {
        maze = new Grid();
        Grid *currRowStart = maze;

        srand(time(0)); // To get random values

        // Allocate maze and link cells
        for (int i = 0; i < s; i++)
        {
            Grid *curr = currRowStart;
            

            for (int j = 0; j < s; j++)
            {
                // Randomly set walls (20% chance), except start and end
                if (i == 0 && j == 0 || i == s - 1 && j == s - 1)
                    curr->setState(0);
                else
                    curr->setState(rand() % 5 == 0 ? 1 : 0);

                if (j < s - 1)
                {
                    curr->setDir(RIGHT, new Grid());
                    curr->getDir(RIGHT)->setDir(LEFT, curr);
                    curr = curr->getDir(RIGHT);
                }
            }

            if (i < s - 1)
            {
                currRowStart->setDir(DOWN, new Grid());
                currRowStart->getDir(DOWN)->setDir(UP, currRowStart);
                currRowStart = currRowStart->getDir(DOWN);
            }
        }
    }
    /*
    function getPath
    This function will find a path between start point and finish point.
    Return a list content the path information inside.
    If there is no path between two point then the list will be empty.

    這個函數會找到起點到終點間的一條路徑
    回傳一個 list 包含著路徑的資訊
    如果找不到路徑的話 list 就會是空的
    */
    bool findPath(Grid *start, Grid *end, List &path)
    {
        if (start == nullptr || start->getState() == 1)
            return false;

        // Add start to path
        path.addElement(start);
        start->setState(1); // Mark as visited

        if (start == end)
            return true;

        // Check each direction
        for (int d = 0; d < 4; d++)
        {
            if (findPath(start->getDir(d), end, path))
                return true;
        }

        // If no direction works, backtrack
        path.removeElement();
        return false;
    }

    List *getPath()
    {
        List *path = new List();

        Grid *end = maze;
        while (end->getDir(RIGHT) != nullptr)
            end = end->getDir(RIGHT);
        while (end->getDir(DOWN) != nullptr)
            end = end->getDir(DOWN);

        if (!findPath(maze, end, *path))
            cout << "No path found." << endl;

        return path;
    };
    void printMaze()
    {
        Grid *j = maze, *k;
        while (j != NULL)
        {
            k = j;
            while (k != NULL)
            {
                cout << k->getState();
                k = k->getDir(RIGHT);
            }
            cout << endl;
            j = j->getDir(DOWN);
        }
    }

private:
    Grid *maze;
};

int main()
{
    Maze *maze = new Maze();
    maze->printMaze();
    maze->getPath()->printPath();
}
