#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 10 // Define the size of the maze to be 10x10

using namespace std;

// Define a class that a single location in the maze
class Node
{
public:
    Node()
        : row(0), col(0) {}

    Node(int r, int c)
        : row(r), col(c) {}

    int getRow() { return row; }
    int getCol() { return col; }

    void setRow(int r)
    {
        if (r >= 0 && r < SIZE)
            row = r;
    }
    void setCol(int c)
    {
        if (c >= 0 && c < SIZE)
            col = c;
    }

private:
    int col, row;
};

class List
{
public:
    List()
    {
        top = 0;
    }
    /*
    function addElement
    Insert an element from list
    */
    void addElement(int r, int c)
    {
        if(top < SIZE * SIZE) {
            data[top] = Node(r, c);
            top ++;
        }
        else {
            cout << "Stack is full. Cannot push element " << endl;
        }
    }
    /*
    function removeElement
    remove an element from list and return a pointer point to the element.
    If list is empty, return NULL.
    */
    Node *removeElement()
    {
        if(top == 0) {
            return NULL;
        }
        else {
            top--;
            return &data[top];
        }

    }
    void printList()
    {
        int j;
        for (j = 0; j < top; j++)
        {
            cout << "(" << data[j].getRow() << ", " << data[j].getCol() << ")" << endl;
        }
    }

private:
    Node data[SIZE * SIZE];
    int top;
};

class Maze
{
public:
    Maze()
    {
        initMaze(SIZE);
    }

    ~Maze()
    {
        for (int i = 0; i < SIZE; i++)
        {
            delete[] maze[i];
        }
        delete[] maze;
    }

    void initMaze(int s)
    {
        maze = new int *[s];
        for (int i = 0; i < s; i++)
        {
            maze[i] = new int[s];
            for (int j = 0; j < s; j++)
            {
                maze[i][j] = 0; // Initialize all cells to 0
            }
        }

        int numWalls = (s * s * 20) / 100; // Number of walls to be generated
        int countWalls = 0;

        srand(time(0)); // Seed for randomness

        while (countWalls < numWalls)
        {
            int randomRow = rand() % s;
            int randomCol = rand() % s;

            if ((randomRow != 0 || randomCol != 0) &&         // Not the starting point
                (randomRow != s - 1 || randomCol != s - 1) && // Not the ending point
                maze[randomRow][randomCol] == 0)              // Not already a wall
            {
                maze[randomRow][randomCol] = 1;
                countWalls++;
            }
        }
    }
    /*
    function getPath
    This function will find a path between start point and finish point.
    Return a list content the path information inside.
    If there is no path between two point then the list will be empty.
    */
    List *getPath()
    {
        List *path = new List();
        bool visited[SIZE][SIZE] = {false};

        if (dfs(0, 0, path, visited))
        {
            return path;
        }

        return new List();
    }

    /** Recursive function that tries to find a path from the current position (row, col) 
    to the end of the maze
     **/
    bool dfs(int row, int col, List *path, bool visited[SIZE][SIZE])
    {
        /**
         Checks if the current location is outside the maze boundary, is a wall, or has been visited
         If any of the above conditions are met, the move is considered invalid and therefore false is returned
         **/
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || maze[row][col] == 1 || visited[row][col])
        {
            return false;
        }

        /**
         Check if the current position is the end of the maze 
         If yes will add it to the path and return true indicating the path was found
         **/
        if (row == SIZE - 1 && col == SIZE - 1)
        {
            path->addElement(row, col);
            return true;
        }

        visited[row][col] = true;   // Mark that the current location has been visited
        path->addElement(row, col); // Add current location to path

        /**
         Try moving in four directions (up, down, left, right) from your current position. For each direction
         this code calls the dfs function recursively. It returns true if the path can be found from any direction
         **/
        if (dfs(row + 1, col, path, visited) || dfs(row - 1, col, path, visited) ||
            dfs(row, col + 1, path, visited) || dfs(row, col - 1, path, visited))
        {
            return true;
        }

        /**
        If the path cannot be found in all directions from the current location
        remove the current location from the path and return to the previous step
         **/
        path->removeElement();
        return false;  // No path can be found from the current location to the end point
    }
    void printMaze()
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < SIZE; k++)
            {
                if (maze[j][k] == 0)
                    cout << " ";
                else if (maze[j][k] == 1)
                    cout << "*";
            }
            cout << "\n";
        }
    }

private:
    int **maze;
};

int main()
{
    Maze *mazeInstance = new Maze();
    mazeInstance->printMaze();
    List *path = mazeInstance->getPath();
    path->printList();
    delete mazeInstance;
    delete path; // Clean up the allocated memory for path
    return 0;
}
