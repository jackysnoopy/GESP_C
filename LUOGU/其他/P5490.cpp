#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Event { long long x, y1, y2; int t; };
bool cmp(const Event &a, const Event &b) { return a.x < b.x; }
vector<long long> ys;
int findY(long long y) { return lower_bound(ys.begin(), ys.end(), y) - ys.begin(); }
int cnt[800004]; long long len[800004];
void pushup(int p, int l, int r) {
    if (cnt[p]) len[p] = ys[r] - ys[l - 1];
    else if (l == r) len[p] = 0;
    else len[p] = len[p*2] + len[p*2+1];
}
void update(int p, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) { cnt[p] += v; pushup(p, l, r); return; }
    int mid = (l + r) / 2;
    if (L < mid) update(p*2, l, mid, L, R, v);
    if (R > mid) update(p*2+1, mid, r, L, R, v);
    pushup(p, l, r);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<Event> ev;
    for (int i = 0; i < n; ++i) {
        long long x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
        ys.push_back(y1); ys.push_back(y2);
        ev.push_back({x1, y1, y2, 1});
        ev.push_back({x2, y1, y2, -1});
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(ev.begin(), ev.end(), cmp);
    long long ans = 0;
    for (int i = 0; i < (int)ev.size(); ++i) {
        if (i > 0) ans += len[1] * (ev[i].x - ev[i-1].x);
        int l = findY(ev[i].y1) + 1, r = findY(ev[i].y2) + 1;
        update(1, 1, (int)ys.size(), l, r, ev[i].t);
    }
    cout << ans << '\n';
    return 0;
}
