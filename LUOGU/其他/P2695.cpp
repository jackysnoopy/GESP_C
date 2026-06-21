#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> heads(n);
    for (int i = 0; i < n; i++) cin >> heads[i];
    vector<pair<int,int>> knights(m);
    for (int i = 0; i < m; i++) cin >> knights[i].first >> knights[i].second;
    sort(heads.begin(), heads.end(), greater<int>());
    sort(knights.begin(), knights.end(), greater<pair<int,int>>());
    long long ans = 0;
    int j = 0;
    bool ok = true;
    for (int i = 0; i < n; i++) {
        while (j < m && (knights[j].first < heads[i] || knights[j].second == 0)) j++;
        if (j >= m) { ok = false; break; }
        ans += knights[j].second;
        j++;
    }
    if (!ok) cout << "you died!" << "\n";
    else cout << ans << "\n";
    return 0;
}
