#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 20005;
int K, N, C;
int seg[MAXN]; // 树状区间最值（线段树更稳，这里用线段树）

struct Group { int s, e, m; };
bool cmp(const Group& a, const Group& b) {
    return a.e < b.e;
}

// 线段树：单点不需，区间 [l,r] 内现已坐人数最大值 + 区间加
struct Seg {
    int mx[MAXN << 2];
    int tag[MAXN << 2];
    void push_down(int o) {
        if (tag[o]) {
            mx[o<<1] += tag[o]; tag[o<<1] += tag[o];
            mx[o<<1|1] += tag[o]; tag[o<<1|1] += tag[o];
            tag[o] = 0;
        }
    }
    void update(int o, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) { mx[o] += v; tag[o] += v; return; }
        push_down(o);
        int m = (l + r) >> 1;
        if (ql <= m) update(o<<1, l, m, ql, qr, v);
        if (qr > m) update(o<<1|1, m+1, r, ql, qr, v);
        mx[o] = max(mx[o<<1], mx[o<<1|1]);
    }
    int query(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return mx[o];
        push_down(o);
        int m = (l + r) >> 1, res = 0;
        if (ql <= m) res = max(res, query(o<<1, l, m, ql, qr));
        if (qr > m) res = max(res, query(o<<1|1, m+1, r, ql, qr));
        return res;
    }
} T;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> K >> N >> C;
    vector<Group> g(K);
    for (int i = 0; i < K; ++i) cin >> g[i].s >> g[i].e >> g[i].m;
    sort(g.begin(), g.end(), cmp);
    long long ans = 0;
    for (auto& x : g) {
        // 区间 [s, e-1] 内（牛 s..e-1 上车段）当前最大占用
        int cur = T.query(1, 1, N - 1, x.s, x.e - 1);
        int can = min(x.m, C - cur);
        if (can > 0) {
            ans += can;
            T.update(1, 1, N - 1, x.s, x.e - 1, can);
        }
    }
    cout << ans << "\n";
    return 0;
}
