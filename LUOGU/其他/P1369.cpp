#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
struct Point { int x, y; };
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    Point p[301];
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    int ans = min(n, 2);
    // Sort by x
    sort(p, p + n, [](const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    // For each pair of distinct x values
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].x == p[j].x) continue;
            int x1 = p[i].x, x2 = p[j].x;
            map<int, int> cnt;
            int total = 0;
            for (int k = 0; k < n; k++) {
                if (p[k].x == x1 || p[k].x == x2) {
                    cnt[p[k].y]++;
                    total++;
                }
            }
            int onEdge = 0;
            for (auto& pr : cnt) {
                if (pr.second == 1) onEdge++;
                else onEdge += 2; // both top and bottom
            }
            // Points on x1 or x2 with y between min and max y
            // Actually: points on left edge + points on right edge + points on top/bottom edges
            // Left edge: all points with x=x1, right edge: all with x=x2
            // Top edge: all points with y=maxY and x1<=x<=x2
            // Bottom edge: all points with y=minY and x1<=x<=x2
            // Total = left + right + top(between) + bottom(between)
            // But we counted left+right already as total
            // Top/bottom between: points with y=minY or y=maxY and x1<x<x2
            int minY = 1e9, maxY = -1e9;
            for (auto& pr : cnt) { minY = min(minY, pr.first); maxY = max(maxY, pr.first); }
            int extra = 0;
            for (int k = 0; k < n; k++) {
                if (p[k].x > x1 && p[k].x < x2 && (p[k].y == minY || p[k].y == maxY))
                    extra++;
            }
            ans = max(ans, total + extra);
        }
    }
    cout << ans << "\n";
    return 0;
}
