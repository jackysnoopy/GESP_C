#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

int n;
vector<int> adj[MAXN];
int K;
bool ok;

int dfs(int u, int parent) {
    vector<int> chains;
    for (int v : adj[u]) {
        if (v == parent) continue;
        int d = dfs(v, u);
        if (!ok) return 0;
        chains.push_back(d);
    }

    if (chains.empty()) {
        return 0;
    }

    sort(chains.begin(), chains.end());

    int left = 0, right = (int)chains.size() - 1;
    int max_unpaired = 0;
    vector<bool> used(chains.size(), false);

    while (left < right) {
        if (chains[left] + chains[right] >= K) {
            used[left] = used[right] = true;
            left++;
            right--;
        } else {
            left++;
        }
    }

    for (int i = 0; i < (int)chains.size(); i++) {
        if (!used[i]) {
            max_unpaired = max(max_unpaired, chains[i]);
        }
    }

    if (u == 1 && max_unpaired > 0) {
        ok = false;
        return 0;
    }

    return max_unpaired + 1;
}

bool check(int k) {
    K = k;
    ok = true;
    dfs(1, 0);
    return ok;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int lo = 1, hi = n - 1;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    printf("%d\n", lo);
    return 0;
}
