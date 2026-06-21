#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, n;
    cin >> c >> n;
    vector<int> times(c);
    for (int i = 0; i < c; i++) cin >> times[i];
    vector<pair<int,int>> cows(n);
    for (int i = 0; i < n; i++) cin >> cows[i].first >> cows[i].second;
    sort(cows.begin(), cows.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second < b.second;
    });
    sort(times.begin(), times.end());
    vector<bool> used(c, false);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a = cows[i].first, b = cows[i].second;
        for (int j = 0; j < c; j++) {
            if (!used[j] && times[j] >= a && times[j] <= b) {
                used[j] = true;
                ans++;
                break;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
