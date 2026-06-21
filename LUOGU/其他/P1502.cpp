#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Event { int x, y, t; };
bool cmp(const Event &a, const Event &b) { return a.x < b.x || (a.x == b.x && a.t < b.t); }
int tree[800004], tag[800004];
vector<int> ys;
void pushup(int p) { tree[p] = max(tree[p*2], tree[p*2+1]) + tag[p]; }
void build(int p, int l, int r) {
    tag[p] = 0; tree[p] = 0;
    if (l == r) return;
    int mid = (l + r) / 2;
    build(p*2, l, mid); build(p*2+1, mid+1, r);
}
void update(int p, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) { tag[p] += v; pushup(p); return; }
    int mid = (l + r) / 2;
    if (L < mid) update(p*2, l, mid, L, R, v);
    if (R > mid) update(p*2+1, mid, r, L, R, v);
    pushup(p);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, w, h; cin >> n >> w >> h;
        vector<Event> ev;
        ys.clear();
        for (int i = 0; i < n; ++i) {
            int x, y; cin >> x >> y;
            ys.push_back(y); ys.push_back(y + h);
            ev.push_back({x, y, 1});
            ev.push_back({x + w, y, -1});
        }
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        auto findY = [](long long y) { return lower_bound(ys.begin(), ys.end(), y) - ys.begin(); };
        sort(ev.begin(), ev.end(), cmp);
        build(1, 0, (int)ys.size() - 1);
        int ans = 0;
        for (auto &e : ev) {
            int l = findY(e.y) + 1, r = findY(e.y + h) + 1;
            update(1, 0, (int)ys.size() - 1, l, r, e.t);
            ans = max(ans, tree[1]);
        }
        cout << ans << '\n';
    }
    return 0;
}
