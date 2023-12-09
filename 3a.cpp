#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <ctype.h>

using namespace std;

void getLeft(vector<vector<char>> &grid, list<char> &left, int i, int j) {
    while(i >= 0 && j >= 0) {
        if(!isdigit(grid[i][j])) {
            break;
        }
        else
        {
            left.push_front(grid[i][j]);
            j--;
        }
    }
}

void getRight(vector<vector<char>> &grid, list<char> &right, int i, int j) {
    while(i < grid.size() && j < grid.size()) {
        if(!isdigit(grid[i][j])) {
            break;
        }
        else
        {
            right.push_back(grid[i][j]);
            j++;
        }
    }
}

int main() {
    ifstream inp;
    inp.open("input.txt");
    string line;

    int sum = 0;
    vector<vector<char>> grid;

    while(getline(inp, line)) {
        vector<char> l;
        for(char c : line) {
            l.push_back(c);
        }
        grid.push_back(l);
    }

    for(int y = 0; y < grid.size(); y++) {
        for(int x = 0; x < grid.size(); x++) {
            if(!isdigit(grid[y][x]) && grid[y][x] != '.') {
                // Left 
                int i = y;
                int j = x-1;
                list<char> left;
                getLeft(grid, left, i, j);
                
                if(left.begin() != left.end()) {
                    cout << string(left.begin(), left.end()) << endl;
                    sum += stoi(string(left.begin(), left.end()));
                }

                // Right
                i = y;
                j = x+1;
                list<char> right;
                getRight(grid, right, i, j);

                if(right.begin() != right.end()) {
                    cout << string(right.begin(), right.end()) << endl;
                    sum += stoi(string(right.begin(), right.end()));
                }

                // Up
                i = y-1;
                j = x-1;
                list<char> upLeft;
                getLeft(grid, upLeft, i, j);
                
                i = y-1;
                j = x;
                char upMid = i >= 0 ? grid[i][j] : '\0';

                i = y-1;
                j = x+1;
                list<char> upRight;
                getRight(grid, upRight, i, j);

                string up = "";
                if(upLeft.begin() != upLeft.end()) {
                    up.append(string(upLeft.begin(), upLeft.end()));
                }
                if(isdigit(upMid)) {
                    up.append(string(1, upMid));
                    if(upRight.begin() != upRight.end()) {
                        up.append(string(upRight.begin(), upRight.end()));
                    }
                }
                else {
                    if(upRight.begin() != upRight.end()) {
                        cout << string(upRight.begin(), upRight.end()) << endl;
                        sum += stoi(string(upRight.begin(), upRight.end()));
                    }
                }
                
                if(up != "") {
                    cout << up << endl;
                    sum += stoi(up);
                }

                // Down
                i = y+1;
                j = x-1;
                list<char> downLeft;
                getLeft(grid, downLeft, i, j);
                
                i = y+1;
                j = x;
                char downMid = i < grid.size() ? grid[i][j] : '\0';

                i = y+1;
                j = x+1;
                list<char> downRight;
                getRight(grid, downRight, i, j);

                string down = "";
                if(downLeft.begin() != downLeft.end()) {
                    down.append(string(downLeft.begin(), downLeft.end()));
                }
                if(isdigit(downMid)) {
                    down.append(string(1, downMid));
                    if(downRight.begin() != downRight.end()) {
                        down.append(string(downRight.begin(), downRight.end()));
                    }
                }
                else {
                    if(downRight.begin() != downRight.end()) {
                        cout << string(downRight.begin(), downRight.end()) << endl;
                        sum += stoi(string(downRight.begin(), downRight.end()));
                    }
                }
                
                if(down != "") {
                    cout << down << endl;
                    sum += stoi(down);
                }
            }
        }
    }

    cout << endl << "SUM: " << sum << endl;

    return 0;
}
