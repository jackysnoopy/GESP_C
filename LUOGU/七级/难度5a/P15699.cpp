#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, long long>> bal(n);
    for (int i = 0; i < n; i++) cin >> bal[i].first >> bal[i].second;
    sort(bal.begin(), bal.end());
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    long long cur = 0;
    int idx = 0, ans = 0;
    while (idx < n || !pq.empty()) {
        while (idx < n && bal[idx].first >= cur) {
            pq.push(bal[idx].second);
            idx++;
        }
        if (!pq.empty()) {
            long long d = pq.top();
            pq.pop();
            cur += d;
            ans++;
        } else if (idx < n) {
            cur = bal[idx].first;
        } else {
            break;
        }
    }
    cout << ans << "\n";
    return 0;
}
