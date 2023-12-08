#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main() {
    ifstream inp;
    inp.open("input.txt");
    string line;

    map<string, char> m = {{"one", '1'}, {"two", '2'}, {"three", '3'}, {"four", '4'}, {"five", '5'},
        {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine", '9'}};

    int sum = 0;
    while(getline(inp, line)) {
        char f = 'a';
        char b = 'a';
        char c;

        for(int i = 0; i < line.size(); i++) {
            c = line[i];

            if(c >= '0' && c <= '9') {
                if(f == 'a') {
                    f = c;
                }
                b = c;

                continue;
            }

            string s = line.substr(i, 3);
            if((i <= line.size() - 3) && (m.count(s) > 0)) {
                 if(f == 'a') {
                    f = m[s];
                }
                b = m[s];

                continue;
            }

            s = line.substr(i, 4);
            if((i <= line.size() - 4) && (m.count(s) > 0)) {
                 if(f == 'a') {
                    f = m[s];
                }
                b = m[s];

                continue;
            }

            s = line.substr(i, 5);
            cout << s << "!" << endl;
            if((i <= line.size() - 5) && (m.count(s) > 0)) {
                 if(f == 'a') {
                    f = m[s];
                }
                b = m[s];

                continue;
            }
        }

        string num = string(1, f).append(string(1, b));
        cout << stoi(num) << endl;
        sum += stoi(num);
    }

    cout << sum << endl;

    return 0;
}
