#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

bool up(vector<vector<char>> &grid, int &steps, int y, int x) {
    return (grid[y][x] == 'S' && steps > 0) || grid[y][x] == '|' || grid[y][x] == 'F' || grid[y][x] == '7';
}

bool down(vector<vector<char>> &grid, int& steps, int y, int x) {
    return (grid[y][x] == 'S' && steps > 0) || grid[y][x] == '|' || grid[y][x] == 'L' || grid[y][x] == 'J';
}

bool left(vector<vector<char>> &grid, int& steps, int y, int x) {
    return (grid[y][x] == 'S' && steps > 0) || grid[y][x] == '-' || grid[y][x] == 'L' || grid[y][x] == 'F';
}

bool right(vector<vector<char>> &grid, int &steps, int y, int x) {
    return (grid[y][x] == 'S' && steps > 0) || grid[y][x] == '-' || grid[y][x] == '7' || grid[y][x] == 'J';
}

// Recursively walk the loop
void path(vector<vector<char>> &grid, int &steps, int y, int x) {
    if(grid[y][x] == 'S') {
        return;
    }

    if(grid[y][x] == '|') {
        if(y - 1 >= 0 && up(grid, steps, y-1, x)) {
            grid[y][x] = '!';
            steps += 1;

            path(grid, steps, y-1, x);
            return;
        }

        if(y + 1 < grid.size() && down(grid, steps, y+1, x)) {
            grid[y][x] = '!';
            steps += 1;

            path(grid, steps, y+1, x);
            return;
        }
    }

    if(grid[y][x] == '-') {
        if(x - 1 >= 0 && left(grid, steps, y, x-1)) {
            grid[y][x] = '_';
            steps += 1;

            path(grid, steps, y, x-1);
            return;
        }

        if(x + 1 < grid.size() && right(grid, steps, y, x+1)) {
            grid[y][x] = '_';
            steps += 1;

            path(grid, steps, y, x+1);
            return;
        }
    }

    if(grid[y][x] == 'L') {
        if(y - 1 >= 0 && up(grid, steps, y-1, x)) {
            grid[y][x] = '\\';
            steps += 1;

            path(grid, steps, y-1, x);
            return;
        }

        if(x + 1 < grid.size() && right(grid, steps, y, x+1)) {
            grid[y][x] = '\\';
            steps += 1;

            path(grid, steps, y, x+1);
            return;
        }
    }

    if(grid[y][x] == 'J') {
        if(y - 1 >= 0 && up(grid, steps, y-1, x)) {
            grid[y][x] = '/';
            steps += 1;

            path(grid, steps, y-1, x);
            return;
        }

        if(x - 1 >= 0 && left(grid, steps, y, x-1)) {
            grid[y][x] = '/';
            steps += 1;

            path(grid, steps, y, x-1);
            return;
        }
    }

    if(grid[y][x] == '7') {
        if(y + 1 < grid.size() && down(grid, steps, y+1, x)) {
            grid[y][x] = '\\';
            steps += 1;

            path(grid, steps, y+1, x);
            return;
        }

        if(x - 1 >= 0 && left(grid, steps, y, x-1)) {
            grid[y][x] = '\\';
            steps += 1;

            path(grid, steps, y, x-1);
            return;
        }
    }

    if(grid[y][x] == 'F') {
        if(y + 1 < grid.size() && down(grid, steps, y+1, x)) {
            grid[y][x] = '/';
            steps += 1;

            path(grid, steps, y+1, x);
            return;
        }

        if(x + 1 < grid.size() && right(grid, steps, y, x+1)) {
            grid[y][x] = '/';
            steps += 1;

            path(grid, steps, y, x+1);
            return;
        }
    }
}

int main() {
    ifstream inp;
    inp.open("input.txt");
    string line;

    vector<vector<char>> grid;

    int steps = 0;

    // Get grid
    while(getline(inp, line)) {
        vector<char> l;
        for(char c : line) {
            l.push_back(c);
        }
        grid.push_back(l);
    }

    // Find S
    int sY = -1;
    int sX = -1;
    for(int y = 0; y < grid.size(); y++) {
        for(int x = 0; x < grid.size(); x++) {
            if(grid[y][x] == 'S') {
                sY = y;
                sX = x;
                break;
            }
        }

        if(sY != -1) {
            break;
        }
    }

    // Start off of sY sX
    if(sY - 1 >= 0 && up(grid, steps, sY-1, sX)) {
        path(grid, steps, sY-1, sX);
    }
    else if(sX - 1 >= 0 && left(grid, steps, sY, sX-1)) {
        path(grid, steps, sY, sX-1);
    }
    else if(sY + 1 < grid.size() && down(grid, steps, sY+1, sX)) {
        path(grid, steps, sY+1, sX);
    }
    else if(sX + 1 < grid.size() && right(grid, steps, sY, sX+1)) {
        path(grid, steps, sY, sX+1);
    }

    // Calculate the longest distance
    int l = (steps / 2) + 1;

    cout << l << endl;

    return 0;
}
