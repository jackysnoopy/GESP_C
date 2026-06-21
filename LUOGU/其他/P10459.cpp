#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cfloat>
using namespace std;

struct Point {
    double x, y;
    int type;
};

double dist(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double solve(vector<Point>& pts, int l, int r) {
    if (l >= r) return DBL_MAX;
    int mid = (l + r) / 2;
    double d = min(solve(pts, l, mid), solve(pts, mid + 1, r));
    
    vector<Point> strip;
    for (int i = l; i <= r; i++)
        if (fabs(pts[i].x - pts[mid].x) < d)
            strip.push_back(pts[i]);
    
    sort(strip.begin(), strip.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });
    
    for (int i = 0; i < (int)strip.size(); i++) {
        for (int j = i + 1; j < (int)strip.size() && strip[j].y - strip[i].y < d; j++) {
            if (strip[i].type != strip[j].type)
                d = min(d, dist(strip[i], strip[j]));
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<Point> pts(2 * n);
        for (int i = 0; i < n; i++) {
            cin >> pts[i].x >> pts[i].y;
            pts[i].type = 0;
        }
        for (int i = n; i < 2 * n; i++) {
            cin >> pts[i].x >> pts[i].y;
            pts[i].type = 1;
        }
        sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
            return a.x < b.x;
        });
        cout << fixed << setprecision(3) << solve(pts, 0, 2 * n - 1) << "\n";
    }
    return 0;
}