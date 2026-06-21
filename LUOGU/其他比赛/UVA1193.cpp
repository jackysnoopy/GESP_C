#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Interval {
    double l, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, d, cas = 0;
    while (cin >> n >> d) {
        if (n == 0 && d == 0) break;
        
        vector<Interval> intervals;
        bool possible = true;
        
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            if (y > d) {
                possible = false;
            } else {
                double dx = sqrt((double)d * d - (double)y * y);
                intervals.push_back({x - dx, x + dx});
            }
        }
        
        if (!possible) {
            cout << "Case " << ++cas << ": -1\n";
            continue;
        }
        
        sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
            return a.r < b.r;
        });
        
        int ans = 0;
        double pos = -1e9;
        for (const auto& inv : intervals) {
            if (pos + 1e-9 < inv.l) {
                ans++;
                pos = inv.r;
            }
        }
        
        cout << "Case " << ++cas << ": " << ans << "\n";
    }
    
    return 0;
}