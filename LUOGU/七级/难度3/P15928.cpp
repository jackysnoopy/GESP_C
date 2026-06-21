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

    int minDist = 1e9;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int dx = points[i].first - points[j].first;
            int dy = points[i].second - points[j].second;
            minDist = min(minDist, dx*dx + dy*dy);
        }
    }

    cout << sqrt(minDist) << "\n";
    return 0;
}
