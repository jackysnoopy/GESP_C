#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
long long a[MAXN], b[MAXN], c[MAXN];
int n;
long long T;

long long cappedSum(long long bi, long long ci, long long x, long long cap) {
    if (x > T) return 0;
    __int128 sum = 0;
    __int128 cap128 = cap;

    if (ci == 0) {
        long long g = max(bi, 1LL);
        __int128 num = T - x + 1;
        sum = num * g;
        if (sum >= cap128) return cap;
        return (long long)sum;
    }

    if (ci > 0) {
        long long j0;
        if (bi + ci >= 1) {
            j0 = 1;
        } else {
            long long num = 1 - bi;
            j0 = (num + ci - 1) / ci;
            if (j0 < 1) j0 = 1;
        }
        long long low = max(j0, x);
        if (low > x) {
            sum += low - x;
            if (sum >= cap128) return cap;
        }
        if (low <= T) {
            __int128 num = T - low + 1;
            __int128 term1 = num * bi;
            __int128 term2 = (__int128)ci * (low + T) * num / 2;
            sum += term1 + term2;
            if (sum >= cap128) return cap;
        }
    } else {
        long long j0;
        if (bi < 1) {
            j0 = 0;
        } else {
            j0 = (bi - 1) / (-ci);
        }
        long long p1_end = min(j0, T);
        if (p1_end >= x) {
            __int128 num = p1_end - x + 1;
            __int128 term1 = num * bi;
            __int128 term2 = (__int128)ci * (x + p1_end) * num / 2;
            sum += term1 + term2;
            if (sum >= cap128) return cap;
        }
        long long p2_start = max(j0 + 1, x);
        if (p2_start <= T) {
            sum += T - p2_start + 1;
            if (sum >= cap128) return cap;
        }
    }
    if (sum >= cap128) return cap;
    return (long long)sum;
}

long long computeL(int i) {
    if (a[i] == 0) return T;
    long long lo = 1, hi = T;
    while (lo < hi) {
        long long mid = (lo + hi + 1) / 2;
        if (cappedSum(b[i], c[i], mid, a[i]) >= a[i]) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    return lo;
}

long long D[MAXN];
int sz[MAXN];

void dfs(int u, int parent) {
    sz[u] = 1;
    vector<pair<long long, int>> children;
    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);
        children.push_back({D[v], sz[v]});
        sz[u] += sz[v];
    }
    sort(children.begin(), children.end());
    D[u] = computeL(u);
    long long sum = 0;
    for (size_t i = 0; i < children.size(); i++) {
        D[u] = min(D[u], children[i].first - 1 - sum);
        sum += children[i].second;
    }
}

bool check(long long T_val) {
    T = T_val;
    for (int i = 1; i <= n; i++) {
        D[i] = 0;
        sz[i] = 0;
    }
    dfs(1, 0);
    return D[1] >= 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) cin >> c[i];

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    long long lo = n, hi = 2000000000000000000LL;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << lo << endl;
    return 0;
}
