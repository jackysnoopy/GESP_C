#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    int k;
    cin >> n >> k;
    vector<pair<long long, long long>> bad(k);
    for (int i = 0; i < k; i++) {
        cin >> bad[i].first >> bad[i].second;
        if (bad[i].first > bad[i].second) swap(bad[i].first, bad[i].second);
    }
    sort(bad.begin(), bad.end());
    long long ans = 0;
    long long pos = 1;
    int idx = 0;
    while (pos <= n) {
        long long minB = n + 1;
        while (idx < k && bad[idx].first < pos) idx++;
        for (int j = idx; j < k; j++) {
            minB = min(minB, bad[j].second);
        }
        long long r = minB - 1;
        if (r < pos) r = pos;
        ans++;
        pos = r + 1;
    }
    cout << ans << "\n";
    return 0;
}
