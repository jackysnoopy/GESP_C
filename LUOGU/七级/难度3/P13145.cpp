#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int C;
        cin >> C;
        vector<int> B(C + 1);
        for (int i = 1; i <= C; i++) cin >> B[i];
        if (B[1] == 0 || B[C] == 0) {
            cout << "Case #" << tc << ": IMPOSSIBLE\n";
            continue;
        }
        vector<int> target(C + 1);
        int ball = 0;
        for (int col = 1; col <= C; col++) {
            for (int j = 0; j < B[col]; j++) { ball++; target[ball] = col; }
        }
        int maxDist = 0;
        for (int i = 1; i <= C; i++) maxDist = max(maxDist, abs(target[i] - i));
        int numRows = maxDist + 1;
        vector<int> pos(C + 1);
        for (int i = 1; i <= C; i++) pos[i] = i;
        vector<string> rows;
        for (int r = 0; r < maxDist; r++) {
            string row(C, '.');
            for (int j = 2; j <= C - 1; j++) {
                bool needRight = false, needLeft = false;
                for (int i = 1; i <= C; i++) {
                    if (pos[i] == j) {
                        if (target[i] > j) needRight = true;
                        else if (target[i] < j) needLeft = true;
                    }
                }
                if (needRight) row[j - 1] = '\\';
                else if (needLeft) row[j - 1] = '/';
            }
            rows.push_back(row);
            vector<int> newPos = pos;
            for (int i = 1; i <= C; i++) {
                if (row[pos[i] - 1] == '\\') newPos[i] = pos[i] + 1;
                else if (row[pos[i] - 1] == '/') newPos[i] = pos[i] - 1;
            }
            pos = newPos;
        }
        rows.push_back(string(C, '.'));
        cout << "Case #" << tc << ": " << numRows << "\n";
        for (string& row : rows) cout << row << "\n";
    }
    return 0;
}
