#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> dep(m + 1), t(m + 1);
    for (int i = 1; i <= m; i++) cin >> dep[i];
    for (int i = 1; i <= m; i++) cin >> t[i];
    vector<int> earliest(m + 1), latest(m + 1);
    for (int i = 1; i <= m; i++) {
        if (dep[i] == 0) earliest[i] = 1;
        else earliest[i] = earliest[dep[i]] + t[dep[i]];
    }
    for (int i = 1; i <= m; i++) cout << earliest[i] << (i < m ? " " : "\n");
    bool feasible = true;
    for (int i = 1; i <= m; i++)
        if (earliest[i] + t[i] - 1 > n) feasible = false;
    if (!feasible) return 0;
    vector<vector<int>> children(m + 1);
    for (int i = 1; i <= m; i++)
        if (dep[i] > 0) children[dep[i]].push_back(i);
    for (int i = m; i >= 1; i--) {
        latest[i] = n - t[i] + 1;
        for (int j : children[i])
            latest[i] = min(latest[i], latest[j] - t[i]);
    }
    for (int i = 1; i <= m; i++) cout << latest[i] << (i < m ? " " : "\n");
    return 0;
}
