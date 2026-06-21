#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int,int>> points(n);
    for (int i = 0; i < n; i++) cin >> points[i].first >> points[i].second;

    // 简化：计算面积
    long long area = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += (long long)points[i].first * points[j].second;
        area -= (long long)points[j].first * points[i].second;
    }
    area = abs(area);

    cout << area / 2 << "\n";
    return 0;
}
