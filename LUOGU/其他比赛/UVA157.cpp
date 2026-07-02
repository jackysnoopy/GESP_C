#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int r, c;
    bool first = true;
    while (cin >> r >> c && (r || c)) {
        if (!first) cout << "\n";
        first = false;
        vector<string> grid(r);
        for (int i = 0; i < r; i++) cin >> grid[i];
        
        vector<string> across, down;
        
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] != '#') {
                    bool startAcross = (j == 0 || grid[i][j-1] == '#');
                    bool startDown = (i == 0 || grid[i-1][j] == '#');
                    if (startAcross && (j + 1 < c && grid[i][j+1] != '#')) {
                        string word = "";
                        for (int k = j; k < c && grid[i][k] != '#'; k++) word += grid[i][k];
                        across.push_back(word);
                    }
                    if (startDown && (i + 1 < r && grid[i+1][j] != '#')) {
                        string word = "";
                        for (int k = i; k < r && grid[k][j] != '#'; k++) word += grid[k][j];
                        down.push_back(word);
                    }
                }
            }
        }
        
        cout << "Across\n";
        for (auto &w : across) cout << w << "\n";
        cout << "Down\n";
        for (auto &w : down) cout << w << "\n";
    }
    return 0;
}
