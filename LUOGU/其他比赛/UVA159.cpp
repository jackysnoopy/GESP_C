#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n;
    bool first = true;
    while (cin >> n && n) {
        if (!first) cout << "\n";
        first = false;
        vector<string> words(n);
        for (int i = 0; i < n; i++) cin >> words[i];
        
        vector<string> h, v;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) h.push_back(words[i]);
            else v.push_back(words[i]);
        }
        
        vector<vector<char>> grid(20, vector<char>(20, ' '));
        int hr = 0;
        for (auto &w : h) {
            for (int j = 0; j < (int)w.size(); j++) {
                grid[hr][j + 2] = w[j];
            }
            hr += 2;
        }
        
        int vc = 0;
        for (auto &w : v) {
            for (int i = 0; i < (int)w.size(); i++) {
                grid[i + 2][vc] = w[i];
            }
            vc += 2;
        }
        
        for (int i = 0; i < 20; i++) {
            bool hasContent = false;
            for (int j = 0; j < 20; j++) {
                if (grid[i][j] != ' ') hasContent = true;
            }
            if (!hasContent) continue;
            for (int j = 0; j < 20; j++) {
                cout << grid[i][j];
            }
            cout << "\n";
        }
    }
    return 0;
}
