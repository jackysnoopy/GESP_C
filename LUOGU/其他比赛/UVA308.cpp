#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Interval {
    double left, right;
    bool operator<(const Interval& o) const {
        return right < o.right;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    double R;
    while (cin >> n >> R) {
        vector<Interval> intervals;
        bool possible = true;

        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            if (y > R) {
                possible = false;
            } else {
                double d = sqrt(R * R - y * y);
                intervals.push_back({x - d, x + d});
            }
        }

        if (!possible || n == 0) {
            cout << "-1\n";
            continue;
        }

        sort(intervals.begin(), intervals.end());

        int count = 0;
        double lastPos = -1e18;
        for (auto& iv : intervals) {
            if (iv.left > lastPos) {
                count++;
                lastPos = iv.right;
            }
        }
        cout << count << "\n";
    }
    return 0;
}
