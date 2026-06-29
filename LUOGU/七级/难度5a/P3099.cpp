#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}
};

vector<Point> convexHull(vector<Point>& pts) {
    int n = pts.size();
    if (n <= 1) return pts;
    
    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    
    vector<Point> hull;
    
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2) {
            Point a = hull[hull.size() - 2];
            Point b = hull[hull.size() - 1];
            ll cross = (b.x - a.x) * (pts[i].y - a.y) - (b.y - a.y) * (pts[i].x - a.x);
            if (cross <= 0) hull.pop_back();
            else break;
        }
        hull.push_back(pts[i]);
    }
    
    int lower = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while ((int)hull.size() > lower) {
            Point a = hull[hull.size() - 2];
            Point b = hull[hull.size() - 1];
            ll cross = (b.x - a.x) * (pts[i].y - a.y) - (b.y - a.y) * (pts[i].x - a.x);
            if (cross <= 0) hull.pop_back();
            else break;
        }
        hull.push_back(pts[i]);
    }
    
    hull.pop_back();
    return hull;
}

bool insideConvexHull(Point p, vector<Point>& hull) {
    int n = hull.size();
    if (n == 0) return false;
    if (n == 1) return p.x == hull[0].x && p.y == hull[0].y;
    if (n == 2) {
        ll cross = (hull[1].x - hull[0].x) * (p.y - hull[0].y) - (hull[1].y - hull[0].y) * (p.x - hull[0].x);
        if (cross != 0) return false;
        return p.x >= min(hull[0].x, hull[1].x) && p.x <= max(hull[0].x, hull[1].x) &&
               p.y >= min(hull[0].y, hull[1].y) && p.y <= max(hull[0].y, hull[1].y);
    }
    
    ll cross1 = (hull[1].x - hull[0].x) * (p.y - hull[0].y) - (hull[1].y - hull[0].y) * (p.x - hull[0].x);
    for (int i = 1; i < n; i++) {
        ll cross2 = (hull[(i + 1) % n].x - hull[i].x) * (p.y - hull[i].y) - (hull[(i + 1) % n].y - hull[i].y) * (p.x - hull[i].x);
        if (cross1 * cross2 < 0) return false;
    }
    
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    
    vector<Point> A(n), B(n);
    for (int i = 0; i < n; i++) scanf("%lld%lld", &A[i].x, &A[i].y);
    for (int i = 0; i < n; i++) scanf("%lld%lld", &B[i].x, &B[i].y);
    
    vector<Point> hullA = convexHull(A);
    vector<Point> hullB = convexHull(B);
    
    int scoreA = 0, scoreB = 0;
    for (int i = 0; i < n; i++) {
        if (insideConvexHull(B[i], hullA)) scoreA++;
        if (insideConvexHull(A[i], hullB)) scoreB++;
    }
    
    printf("%d %d\n", scoreA, scoreB);
    
    return 0;
}
