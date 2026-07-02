#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    while (cin >> s) {
        string a = s.substr(0, 6);
        string b = s.substr(6, 6);
        // Precompute all 24 orientations of a cube
        // Standard cube orientations
        int orient[24][6] = {
            {0,1,2,3,4,5}, {0,2,4,1,3,5}, {0,4,3,2,1,5}, {0,3,1,4,2,5},
            {5,1,3,2,4,0}, {5,2,1,4,3,0}, {5,4,2,1,3,0}, {5,3,4,1,2,0},
            {1,0,2,5,4,3}, {1,2,4,0,5,3}, {1,4,5,2,0,3}, {1,5,0,4,2,3},
            {4,0,1,3,5,2}, {4,1,3,5,0,2}, {4,3,5,0,1,2}, {4,5,0,1,3,2},
            {3,0,4,1,5,2}, {3,4,5,0,1,2}, {3,5,0,4,1,2}, {3,1,0,5,4,2},
            {2,0,5,1,4,3}, {2,5,4,0,1,3}, {2,4,1,5,0,3}, {2,1,0,4,5,3}
        };
        bool ok = false;
        for (int o = 0; o < 24 && !ok; o++) {
            bool match = true;
            for (int i = 0; i < 6; i++) {
                if (a[i] != b[orient[o][i]]) {
                    match = false;
                    break;
                }
            }
            if (match) ok = true;
        }
        cout << (ok ? "TRUE" : "FALSE") << endl;
    }
    return 0;
}
