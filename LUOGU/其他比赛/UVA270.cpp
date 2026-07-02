#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int T;
    cin >> T;
    bool first = true;
    while (T--) {
        int n;
        cin >> n;
        vector<Point> pts(n);
        for (int i = 0; i < n; i++) {
            cin >> pts[i].x >> pts[i].y;
        }
        
        int ans = 1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int cnt = 2;
                int dx = pts[j].x - pts[i].x;
                int dy = pts[j].y - pts[i].y;
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) continue;
                    int dx2 = pts[k].x - pts[i].x;
                    int dy2 = pts[k].y - pts[i].y;
                    if (dx * dy2 == dy * dx2) {
                        cnt++;
                    }
                }
                ans = max(ans, cnt);
            }
        }
        
        if (!first) cout << "\n";
        first = false;
        cout << ans << "\n";
    }
    return 0;
}
