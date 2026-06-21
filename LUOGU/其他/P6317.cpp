#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> r(n), c(n);
    for (int i = 0; i < n; i++) cin >> r[i] >> c[i];
    vector<int> rowPos(n), colPos(n);
    for (int i = 0; i < n; i++) { rowPos[i] = r[i]; colPos[i] = c[i]; }
    sort(rowPos.begin(), rowPos.end());
    sort(colPos.begin(), colPos.end());
    vector<int> targetRow(n), targetCol(n);
    for (int i = 0; i < n; i++) { targetRow[i] = rowPos[i]; targetCol[i] = colPos[i]; }
    vector<pair<int,char>> moves;
    for (int i = 0; i < n; i++) {
        int curR = r[i], curC = c[i];
        int tarR = targetRow[i], tarC = targetCol[i];
        while (curR > tarR) { moves.push_back({i+1, 'U'}); curR--; }
        while (curR < tarR) { moves.push_back({i+1, 'D'}); curR++; }
        while (curC > tarC) { moves.push_back({i+1, 'L'}); curC--; }
        while (curC < tarC) { moves.push_back({i+1, 'R'}); curC++; }
    }
    cout << moves.size() << "\n";
    for (auto& m : moves) {
        cout << m.first << " " << m.second << "\n";
    }
    return 0;
}
