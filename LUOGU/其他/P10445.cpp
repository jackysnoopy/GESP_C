#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    ll m;
    int p;
    cin >> n >> m >> p;
    vector<ll> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    struct Point { ll coord; int idx; };
    vector<Point> pts(n);
    for (int i = 0; i < n; i++) pts[i] = {x[i], i + 1};
    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        if (abs(a.coord) != abs(b.coord)) return abs(a.coord) < abs(b.coord);
        return a.idx < b.idx;
    });
    auto compute_time = [](const vector<Point>& sorted, int k) -> ll {
        ll max_left = 0, max_right = 0;
        for (int i = 0; i < k; i++) {
            if (sorted[i].coord < 0) max_left = max(max_left, -sorted[i].coord);
            else max_right = max(max_right, sorted[i].coord);
        }
        return 2 * max_left + 2 * max_right;
    };
    int best_k_no_gift = 0;
    { int lo = 0, hi = n;
      while (lo < hi) { int mid = (lo + hi + 1) / 2;
        if (compute_time(pts, mid) <= m) lo = mid; else hi = mid - 1; }
      best_k_no_gift = lo; }
    int best_k_with_gift = best_k_no_gift;
    { for (int k = best_k_no_gift + 1; k <= min(n, best_k_no_gift + 10); k++) {
        ll max_left = 0, max_right = 0;
        bool includes_gift = false;
        for (int i = 0; i < k; i++) {
            if (pts[i].idx == p) includes_gift = true;
            ll coord = pts[i].coord;
            if (coord < 0) max_left = max(max_left, -coord);
            else max_right = max(max_right, coord);
        }
        ll time_needed = 2 * max_left + 2 * max_right;
        if (includes_gift && time_needed <= m + 5) best_k_with_gift = k;
        else if (!includes_gift) {
            max_left = 0; max_right = 0;
            for (int i = 0; i < k - 1; i++) {
                ll coord = pts[i].coord;
                if (coord < 0) max_left = max(max_left, -coord);
                else max_right = max(max_right, coord);
            }
            ll gcoord = x[p - 1];
            if (gcoord < 0) max_left = max(max_left, -gcoord);
            else max_right = max(max_right, gcoord);
            time_needed = 2 * max_left + 2 * max_right;
            if (time_needed <= m + 5) best_k_with_gift = k;
        }
      } }
    int ans = max(best_k_no_gift, best_k_with_gift);
    bool use_gift = (best_k_with_gift > best_k_no_gift && best_k_with_gift == ans);
    vector<int> selected;
    if (use_gift) {
        bool has_gift = false;
        for (int i = 0; i < ans; i++) if (pts[i].idx == p) has_gift = true;
        for (int i = 0; i < ans; i++) selected.push_back(pts[i].idx);
        if (!has_gift) { selected.pop_back(); selected.push_back(p); }
    } else {
        for (int i = 0; i < ans; i++) selected.push_back(pts[i].idx);
    }
    vector<int> left_pts, right_pts;
    for (int idx : selected) {
        if (x[idx - 1] < 0) left_pts.push_back(idx);
        else right_pts.push_back(idx);
    }
    sort(left_pts.begin(), left_pts.end(), [&](int a, int b) { return x[a-1] > x[b-1]; });
    sort(right_pts.begin(), right_pts.end(), [&](int a, int b) { return x[a-1] < x[b-1]; });
    vector<int> order;
    for (int i = (int)right_pts.size() - 1; i >= 0; i--) order.push_back(right_pts[i]);
    for (int i = (int)left_pts.size() - 1; i >= 0; i--) order.push_back(left_pts[i]);
    cout << ans << "\n";
    for (int i = 0; i < ans; i++) { if (i) cout << " "; cout << order[i]; }
    cout << "\n";
    return 0;
}
