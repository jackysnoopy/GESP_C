#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<pair<int, int>> adj[50005];
int ans;

int dfs(int u, int p, int mid) {
    vector<int> paths;
    int extra = 0;
    for (int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i].first, w = adj[u][i].second;
        if (v == p) continue;
        int d = dfs(v, u, mid);
        if (d + w >= mid) {
            extra++;
        } else {
            paths.push_back(d + w);
        }
    }
    // Match paths: pair up paths that sum >= mid
    sort(paths.begin(), paths.end());
    int l = 0, r = (int)paths.size() - 1;
    while (l < r) {
        if (paths[l] + paths[r] >= mid) {
            extra++;
            l++;
            r--;
        } else {
            l++;
        }
    }
    // Return the longest unmatched path to parent
    if (paths.size() % 2 == 1) {
        return paths[paths.size() / 2];
    }
    return 0;
}

bool check(int mid) {
    int cnt = dfs(1, 0, mid);
    return cnt >= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        adj[a].push_back({b, l});
        adj[b].push_back({a, l});
    }
    int lo = 0, hi = 1e9;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
    return 0;
}
