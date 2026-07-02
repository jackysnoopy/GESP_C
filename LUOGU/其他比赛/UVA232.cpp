#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int r, c;
    int t = 0;
    while (cin >> r >> c && r && c) {
        vector<string> grid(r);
        for (int i = 0; i < r; i++) cin >> grid[i];
        if (t++) cout << "\n";
        cout << "puzzle #" << t << ":\n";
        vector<int> across(r, 0);
        vector<int> down(c, 0);
        int num = 1;
        vector<vector<int>> labels(r, vector<int>(c, 0));
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] != '*') {
                    bool need = false;
                    if (i == 0 || j == 0 || grid[i-1][j] == '*' || grid[i][j-1] == '*')
                        need = true;
                    if (need) {
                        labels[i][j] = num++;
                    }
                }
            }
        }
        cout << "Across\n";
        for (int i = 0; i < r; i++) {
            int j = 0;
            while (j < c) {
                if (grid[i][j] != '*') {
                    if (j == 0 || grid[i][j-1] == '*') {
                        if (labels[i][j] > 0) {
                            cout << labels[i][j] << ".";
                            int start = j;
                            while (j < c && grid[i][j] != '*') j++;
                            cout << grid[i].substr(start, j - start) << "\n";
                        }
                    }
                }
                j++;
            }
        }
        cout << "Down\n";
        for (int j = 0; j < c; j++) {
            int i = 0;
            while (i < r) {
                if (grid[i][j] != '*') {
                    if (i == 0 || grid[i-1][j] == '*') {
                        if (labels[i][j] > 0) {
                            cout << labels[i][j] << ".";
                            int start = i;
                            while (i < r && grid[i][j] != '*') i++;
                            for (int k = start; k < i; k++) cout << grid[k][j];
                            cout << "\n";
                        }
                    }
                }
                i++;
            }
        }
    }
    return 0;
}
