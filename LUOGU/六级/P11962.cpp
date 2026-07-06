#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> depth(n + 1, -1);
    vector<int> stk = {1};
    depth[1] = 0;
    while (!stk.empty()) {
        int u = stk.back();
        stk.pop_back();
        for (int v : g[u]) {
            if (depth[v] == -1) {
                depth[v] = depth[u] + 1;
                stk.push_back(v);
            }
        }
    }

    int cnt_even = 0, cnt_odd = 0;
    for (int i = 1; i <= n; i++) {
        if (depth[i] % 2 == 0) cnt_even++;
        else cnt_odd++;
    }

    for (int i = 1; i <= n; i++) {
        if (depth[i] % 2 == 0) cout << cnt_even;
        else cout << cnt_odd;
        if (i < n) cout << " ";
    }
    cout << endl;

    return 0;
}
