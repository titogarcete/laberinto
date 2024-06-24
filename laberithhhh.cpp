#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Maze {
private:
    int width, height;
    vector<vector<char>> maze;
    vector<vector<bool>> visited;
    
    const char WALL = '#';
    const char PATH = '*';
    const char START = 'S';
    const char END = 'E';
    
    void initializeMaze() {
        maze.resize(height, vector<char>(width, WALL));
        visited.resize(height, vector<bool>(width, false));
    }
    
    bool isValid(int x, int y) {
        return (x >= 0 && x < height && y >= 0 && y < width);
    }
    
    void generateMaze(int x, int y) {
        visited[x][y] = true;
        maze[x][y] = PATH;
        
        vector<pair<int, int>> directions = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};
        random_shuffle(directions.begin(), directions.end());
        
        for (auto dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            
            if (isValid(nx, ny) && !visited[nx][ny]) {
                maze[(x + nx) / 2][(y + ny) / 2] = PATH;
                generateMaze(nx, ny);
            }
        }
    }
    
    bool solveMaze() {
        queue<pair<int, int>> q;
        vector<vector<bool>> visitedSolve(height, vector<bool>(width, false));
        vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width, {-1, -1}));
        
        q.push({0, 0});
        visitedSolve[0][0] = true;
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            if (x == height - 1 && y == width - 1) {
                while (x != 0 || y != 0) {
                    maze[x][y] = PATH;
                    tie(x, y) = parent[x][y];
                }
                return true;
            }
            
            vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            
            for (auto dir : directions) {
                int nx = x + dir.first;
                int ny = y + dir.second;
                
                if (isValid(nx, ny) && maze[nx][ny] != WALL && !visitedSolve[nx][ny]) {
                    q.push({nx, ny});
                    visitedSolve[nx][ny] = true;
                    parent[nx][ny] = {x, y};
                }
            }
        }
        
        return false;
    }
    
public:
    Maze(int w, int h) : width(w), height(h) {
        initializeMaze();
    }
    
    void createMaze() {
        srand(time(0));
        generateMaze(0, 0);
        maze[0][0] = START;
        maze[height - 1][width - 1] = END;
    }
    
    void printMaze() {
        for (const auto &row : maze) {
            for (const auto &cell : row) {
                cout << cell << ' ';
            }
            cout << endl;
        }
    }
    
    bool findSolution() {
        return solveMaze();
    }
};

int main() {
    int width, height;
    
    cout << "Ingrese el ancho del laberinto: ";
    cin >> width;
    cout << "Ingrese la altura del laberinto: ";
    cin >> height;
    
    // Ensure the dimensions are odd
    if (width % 2 == 0) width++;
    if (height % 2 == 0) height++;
    
    Maze maze(width, height);
    maze.createMaze();
    maze.printMaze();
    
    if (maze.findSolution()) {
        cout << "Solucion encontrada:" << endl;
        maze.printMaze();
    } else {
        cout << "No se encontro solucion." << endl;
    }
    
    return 0;
}
