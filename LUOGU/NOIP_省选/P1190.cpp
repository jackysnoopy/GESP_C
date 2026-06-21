#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < m && i < n; i++) pq.push(w[i]);
    for (int i = m; i < n; i++) {
        int t = pq.top(); pq.pop();
        pq.push(t + w[i]);
    }
    int ans = 0;
    while (!pq.empty()) {
        ans = pq.top(); pq.pop();
    }
    cout << ans << "\n";
    return 0;
}
