#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double EPS = 1e-9;

struct Circle {
    double x, y, r;
};

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<Circle> circles(n);
        for (int i = 0; i < n; i++) {
            cin >> circles[i].x >> circles[i].y >> circles[i].r;
        }
        
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double d = dist(circles[i].x, circles[i].y, circles[j].x, circles[j].y);
                double r1 = circles[i].r, r2 = circles[j].r;
                
                if (d > r1 + r2 + EPS) continue;
                if (d < fabs(r1 - r2) - EPS) continue;
                if (d < EPS && fabs(r1 - r2) < EPS) continue;
                
                cnt++;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}
