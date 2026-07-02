#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Point {
    double x, y;
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
    vector<Point> hull;
    for (int i = 0; i < n; ++i) {
        while (hull.size() >= 2 && cross(hull[hull.size()-2], hull[hull.size()-1], P[i]) <= 0)
            hull.pop_back();
        hull.push_back(P[i]);
    }
    int k = hull.size();
    for (int i = n - 2; i >= 0; --i) {
        while (hull.size() >= k + 1 && cross(hull[hull.size()-2], hull[hull.size()-1], P[i]) <= 0)
            hull.pop_back();
        hull.push_back(P[i]);
    }
    hull.pop_back();
    return hull;
}

double dist(const Point& a, const Point& b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double rotatingCalipers(const vector<Point>& hull) {
    int n = hull.size();
    if (n <= 1) return 0;
    if (n == 2) return dist(hull[0], hull[1]);
    double maxDist = 0;
    int j = 1;
    for (int i = 0; i < n; i++) {
        int ni = (i + 1) % n;
        while (abs(cross(hull[i], hull[ni], hull[(j+1)%n])) >
               abs(cross(hull[i], hull[ni], hull[j])))
            j = (j + 1) % n;
        maxDist = max(maxDist, max(dist(hull[i], hull[j]), dist(hull[ni], hull[j])));
    }
    return maxDist;
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<Point> points(n);
        for (int i = 0; i < n; i++)
            cin >> points[i].x >> points[i].y;
        vector<Point> hull = convexHull(points);
        double d = rotatingCalipers(hull);
        printf("%.4f\n", d);
    }
    return 0;
}
