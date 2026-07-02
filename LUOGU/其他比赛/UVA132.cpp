// UVA132 - Bumpy Objects (颠簸物体)
// 判断多边形是否能在给定宽度的通道中通过
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>
using namespace std;

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
};

double cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convexHull(vector<Point>& P) {
    int n = P.size();
    if (n <= 1) return P;
    sort(P.begin(), P.end(), [](const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    vector<Point> H(2 * n);
    int k = 0;
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k - 1);
    return H;
}

double dist(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// 旋转卡壳求最小宽度
double minWidth(vector<Point>& hull) {
    int n = hull.size();
    if (n <= 2) return 0;
    double ans = 1e18;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        Point edge = {hull[j].x - hull[i].x, hull[j].y - hull[i].y};
        double len = sqrt(edge.x * edge.x + edge.y * edge.y);
        double maxDist = 0;
        for (int k = 0; k < n; k++) {
            if (k == i || k == j) continue;
            double d = fabs(cross(hull[i], hull[j], hull[k])) / len;
            maxDist = max(maxDist, d);
        }
        ans = min(ans, maxDist);
    }
    return ans;
}

int main() {
    char id;
    int n;
    while (scanf(" %c", &id) == 1 && id != '#') {
        scanf("%d", &n);
        vector<Point> pts(n);
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", &pts[i].x, &pts[i].y);
        }
        vector<Point> hull = convexHull(pts);
        double w = minWidth(hull);
        printf("%c\n%.2f\n", id, w);
    }
    return 0;
}
