#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Building {
    int left, height, right;
};

int main() {
    vector<vector<int>> skyline(10001, vector<int>(201, 0));
    int n;
    bool first = true;
    while (cin >> n) {
        vector<Building> buildings(n);
        for (int i = 0; i < n; i++) {
            cin >> buildings[i].left >> buildings[i].height >> buildings[i].right;
        }
        if (!first) cout << "\n";
        first = false;
        for (int i = 0; i < n; i++) {
            for (int j = buildings[i].left; j < buildings[i].right; j++) {
                skyline[j][i] = max(skyline[j][i], buildings[i].height);
            }
        }
        for (int i = 0; i < n; i++) {
            int max_h = 0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    max_h = max(max_h, skyline[buildings[j].left][j]);
                }
            }
            cout << buildings[i].left << " " << buildings[i].height << " "
                 << buildings[i].right << " " << max_h << "\n";
        }
        for (int i = 0; i < 10001; i++) {
            for (int j = 0; j < 201; j++) {
                skyline[i][j] = 0;
            }
        }
    }
    return 0;
}
