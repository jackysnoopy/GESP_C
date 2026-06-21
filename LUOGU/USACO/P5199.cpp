#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int,int>> peaks(n);
    for (int i = 0; i < n; i++) {
        cin >> peaks[i].first >> peaks[i].second;
    }
    sort(peaks.begin(), peaks.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second > b.second;
    });
    int ans = 0;
    for (int i = 0; i < n; i++) {
        bool visible = true;
        for (int j = 0; j < i; j++) {
            int dx = abs(peaks[i].first - peaks[j].first);
            int dy = abs(peaks[i].second - peaks[j].second);
            if (dx <= dy) {
                visible = false;
                break;
            }
        }
        if (visible) ans++;
    }
    cout << ans << "\n";
    return 0;
}
