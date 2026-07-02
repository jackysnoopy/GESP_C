#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    bool first = true;
    while (true) {
        vector<string> grid(5);
        bool valid = true;
        int blank_r = -1, blank_c = -1;
        for (int i = 0; i < 5; i++) {
            if (!getline(cin, grid[i])) { valid = false; break; }
            if (grid[i].length() < 5) {
                string tmp = grid[i];
                grid[i] = tmp + string(5 - tmp.length(), ' ');
            }
            grid[i] = grid[i].substr(0, 5);
            for (int j = 0; j < 5; j++) {
                if (grid[i][j] == ' ') {
                    blank_r = i;
                    blank_c = j;
                }
            }
        }
        if (!valid) break;
        if (grid[0][0] == 'Z') break;
        if (!first) cout << "\n";
        first = false;
        string moves;
        getline(cin, moves);
        bool ok = true;
        for (char c : moves) {
            if (c == '\n' || c == '\r') continue;
            int nr = blank_r, nc = blank_c;
            if (c == 'A') nr--;
            else if (c == 'B') nr++;
            else if (c == 'L') nc--;
            else if (c == 'R') nc++;
            if (nr < 0 || nr >= 5 || nc < 0 || nc >= 5) {
                ok = false;
                break;
            }
            grid[blank_r][blank_c] = grid[nr][nc];
            grid[nr][nc] = ' ';
            blank_r = nr;
            blank_c = nc;
        }
        if (!ok) {
            cout << "This puzzle has no final configuration.\n";
        } else {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (j) cout << " ";
                    cout << grid[i][j];
                }
                cout << "\n";
            }
        }
    }
    return 0;
}
