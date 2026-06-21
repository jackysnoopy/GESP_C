#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long m;
    cin >> n >> m;
    vector<pair<long long,long long>> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    sort(a.begin(), a.end());
    priority_queue<long long> pq;
    long long sum = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].first > m) continue;
        pq.push(a[i].second);
        sum += a[i].second;
        while (!pq.empty() && a[i].first + sum > m) {
            sum -= pq.top();
            pq.pop();
        }
        ans = max(ans, (int)pq.size());
    }
    cout << ans << "\n";
    return 0;
}
