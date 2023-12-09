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
            if(grid[y][x] == '*') {
                string fst = "";
                string snd = "";

                // Left 
                int i = y;
                int j = x-1;
                list<char> left;
                getLeft(grid, left, i, j);
                
                if(left.begin() != left.end()) {
                    if (fst == "") {
                        cout << "fst left" << endl;
                        fst = string(left.begin(), left.end());
                    }
                    else if (snd == "") {
                        cout << "snd left" << endl;
                        snd = string(left.begin(), left.end());
                    }
                    else {
                        continue;
                    }
                }

                // Right
                i = y;
                j = x+1;
                list<char> right;
                getRight(grid, right, i, j);

                if(right.begin() != right.end()) {
                    if (fst == "") {
                        cout << "fst right" << endl;
                        fst = string(right.begin(), right.end());
                    }
                    else if (snd == "") {
                        cout << "snd right" << endl;
                        snd = string(right.begin(), right.end());
                    }
                    else {
                        continue;
                    }
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
                        if (fst == "") {
                            cout << "fst upright" << endl;
                            fst = string(upRight.begin(), upRight.end());
                        }
                        else if (snd == "") {
                            cout << "snd upright" << endl;
                            snd = string(upRight.begin(), upRight.end());
                        }
                        else {
                            continue;
                        }
                    }
                }
                
                if(up != "") {
                    if (fst == "") {
                        cout << "fst up" << endl;
                        fst = up;
                    }
                    else if (snd == "") {
                        cout << "snd up" << endl;
                        snd = up;
                    }
                    else {
                        continue;
                    }
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
                        if (fst == "") {
                            fst = string(downRight.begin(), downRight.end());
                        }
                        else if (snd == "") {
                            snd = string(downRight.begin(), downRight.end());
                        }
                        else {
                            continue;
                        }
                    }
                }
                
                if(down != "") {
                    if (fst == "") {
                        fst = down;
                    }
                    else if (snd == "") {
                        snd = down;
                    }
                    else {
                        continue;
                    }
                }

                if(fst != "" && snd != "") {
                    sum += (stoi(fst) * stoi(snd));
                }
            }
        }
    }

    cout << endl << "SUM: " << sum << endl;

    return 0;
}
