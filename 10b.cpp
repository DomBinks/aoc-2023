#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

void fill(vector<vector<char>> &grid, int y, int x, char f) {
    if(grid[y][x] == '.') {
        grid[y][x] = f;

        if(y - 1 >= 0 && x - 1 >= 0) {
            fill(grid, y-1, x-1, f);
        }

        if(y - 1 >= 0) {
            fill(grid, y-1, x, f);
        }

        if(y - 1 >= 0 && x + 1 < grid[0].size()) {
            fill(grid, y-1, x+1, f);
        }

        if(y + 1 < grid.size() && x - 1 >= 0) {
            fill(grid, y+1, x-1, f);
        }

        if(y + 1 < grid.size()) {
            fill(grid, y+1, x, f);
        }

        if(y + 1 < grid.size() && x + 1 < grid[0].size()) {
            fill(grid, y+1, x+1, f);
        }

        if(x - 1 >= 0) {
            fill(grid, y, x-1, f);
        }

        if(x + 1 < grid[0].size()) {
            fill(grid, y, x+1, f);
        }
    }
}

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

        if(x + 1 < grid[0].size() && right(grid, steps, y, x+1)) {
            grid[y][x] = '_';
            steps += 1;

            path(grid, steps, y, x+1);
            return;
        }
    }

    if(grid[y][x] == 'L') {
        if(y - 1 >= 0 && up(grid, steps, y-1, x)) {
            grid[y][x] = 'l';
            steps += 1;

            path(grid, steps, y-1, x);
            return;
        }

        if(x + 1 < grid[0].size() && right(grid, steps, y, x+1)) {
            grid[y][x] = 'l';
            steps += 1;

            path(grid, steps, y, x+1);
            return;
        }
    }

    if(grid[y][x] == 'J') {
        if(y - 1 >= 0 && up(grid, steps, y-1, x)) {
            grid[y][x] = 'j';
            steps += 1;

            path(grid, steps, y-1, x);
            return;
        }

        if(x - 1 >= 0 && left(grid, steps, y, x-1)) {
            grid[y][x] = 'j';
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
            grid[y][x] = 'f';
            steps += 1;

            path(grid, steps, y+1, x);
            return;
        }

        if(x + 1 < grid[0].size() && right(grid, steps, y, x+1)) {
            grid[y][x] = 'f';
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
    int enclosed = 0;

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
        for(int x = 0; x < grid[0].size(); x++) {
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

    // Print grid
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;

    // Get the path of the pipe
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

    // Remove unused pipes
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            if(grid[i][j] == '|' || grid[i][j] == '-' || grid[i][j] == 'F' ||
               grid[i][j] == '7' || grid[i][j] == 'L' || grid[i][j] == 'J') {

                grid[i][j] = '.';
            }
        }
    }

    // Flood fill edges
    for(int i = 0; i < grid.size(); i++) {
        fill(grid, i, 0, '0');
        fill(grid, i, grid[0].size() - 1, '0');
    }
    for(int i = 0; i < grid[0].size(); i++) {
        fill(grid, 0, i, '0');
        fill(grid, grid.size() - 1, i, '0');
    }

    // Flood fill left over '.' with 0 or 1
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            if(grid[i][j] == '.') {
                int x = j;
                bool parity = false;
                bool u = false;
                while(x >= 0 && grid[i][x] != '0') {
                    if(grid[i][x] == '!') {
                        parity = !parity;
                    }
                    else if(grid[i][x] == 'j') {
                        u = true;
                    }
                    else if(grid[i][x] == '\\') {
                        u = false;
                    }
                    else if(grid[i][x] == 'l') {
                        if(u == false) {
                            parity = !parity;
                        }
                    }
                    else if(grid[i][x] == 'f') {
                        if(u == true) {
                            parity = !parity;
                        }
                    }

                    x--;
                }
                
                char g = '\0';
                if(parity == false) {
                    g = '0';
                }
                else {
                    g = '1';
                }

                fill(grid, i, j, g);
            }
        }
    }

    // Count the 1s
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            if(grid[i][j] == '1') {
                enclosed++;
            }
        }
    }

    // Print the grid
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;

    cout << enclosed << endl;

    return 0;
}
