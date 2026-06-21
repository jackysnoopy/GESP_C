#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, d;
    cin >> n >> d;
    vector<pair<double, double>> intervals;
    bool possible = true;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if (y > d) { possible = false; continue; }
        double dx = sqrt((double)d * d - (double)y * y);
        intervals.push_back({x - dx, x + dx});
    }
    if (!possible) { cout << -1 << "\n"; return 0; }
    sort(intervals.begin(), intervals.end(), [](const pair<double,double>& a, const pair<double,double>& b) {
        return a.second < b.second;
    });
    int count = 0;
    double last = -1e18;
    for (auto& iv : intervals) {
        if (iv.first > last) {
            count++;
            last = iv.second;
        }
    }
    cout << count << "\n";
    return 0;
}
