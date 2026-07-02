# UVA132 - Bumpy Objects (颠簸物体)

## 题目描述

给定一个多边形（由其顶点定义），判断一个给定直径的圆柱体是否能够通过该多边形所表示的通道。

## 算法思路

1. **凸包构建**：首先计算给定点集的凸包
2. **旋转卡壳**：使用旋转卡壳算法求凸包的最小宽度
3. **判断通过**：如果圆柱体直径小于凸包最小宽度，则可以通过

## 复杂度分析

- 时间复杂度：O(n log n)，其中 n 是顶点数
- 空间复杂度：O(n)

## 代码实现

```cpp
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
```

## 样例说明

输入多边形顶点坐标，输出物体标识和最小宽度。
