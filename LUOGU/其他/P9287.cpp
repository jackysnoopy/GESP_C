#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<int>> order(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cin >> order[i][j];
        --order[i][0];
    }
    int p;
    cin >> p;
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) if (order[i][j] == i) { pos[i] = j; break; }
    }
    int possible = 0;
    for (int i = 0; i < n; ++i) if (order[i][0] == i) ++possible;
    int mandatory = 0;
    for (int i = 0; i < n; ++i) {
        bool ok = true;
        for (int j = 0; j < i; ++j) if (pos[j] > pos[i]) { ok = false; break; }
        if (ok) ++mandatory;
    }
    cout << possible << '\n' << mandatory << '\n';
    return 0;
}
