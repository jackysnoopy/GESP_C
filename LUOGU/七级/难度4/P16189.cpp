#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int cuts = 0;

    function<int(int, int)> dfs = [&](int u, int p) -> int {
        int sum = h[u];
        for (int v : adj[u]) {
            if (v != p) {
                sum += dfs(v, u);
            }
        }
        if (sum > k) {
            cuts++;
            return 0;
        }
        return sum;
    };

    dfs(0, -1);

    cout << cuts << "\n";
    return 0;
}
