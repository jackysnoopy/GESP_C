#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> detectors(n);
    for (int i = 0; i < n; i++) {
        cin >> detectors[i].first >> detectors[i].second;
    }
    sort(detectors.begin(), detectors.end());
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, detectors[i].second);
    }
    for (int i = 0; i < n - 1; i++) {
        int gap = detectors[i + 1].first - detectors[i].first - 1;
        ans = max(ans, min(detectors[i].second, detectors[i + 1].second) + gap);
    }
    cout << ans << "\n";
    return 0;
}
