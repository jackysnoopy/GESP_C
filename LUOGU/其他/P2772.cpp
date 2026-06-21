#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int,int>> pts(n);
    for (int i = 0; i < n; i++) cin >> pts[i].first >> pts[i].second;
    sort(pts.begin(), pts.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        if (a.first == b.first) return a.second > b.second;
        return a.first < b.first;
    });
    vector<pair<int,int>> result;
    int maxY = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (pts[i].second > maxY) {
            result.push_back(pts[i]);
            maxY = pts[i].second;
        }
    }
    reverse(result.begin(), result.end());
    for (int i = 0; i < (int)result.size(); i++) {
        if (i > 0) cout << ",";
        cout << "(" << result[i].first << "," << result[i].second << ")";
    }
    cout << "\n";
    return 0;
}
