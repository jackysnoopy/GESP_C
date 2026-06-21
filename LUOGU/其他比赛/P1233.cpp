#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> sticks(n);
    for (int i = 0; i < n; i++) {
        cin >> sticks[i].first >> sticks[i].second;
    }
    sort(sticks.begin(), sticks.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second > b.second;
    });
    vector<int> dp;
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(dp.begin(), dp.end(), sticks[i].second) - dp.begin();
        if (pos == (int)dp.size()) dp.push_back(sticks[i].second);
        else dp[pos] = sticks[i].second;
    }
    cout << dp.size() << "\n";
    return 0;
}
