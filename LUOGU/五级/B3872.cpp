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
    vector<pair<int,int>> tasks(n);
    for (int i = 0; i < n; i++) cin >> tasks[i].first;
    for (int i = 0; i < n; i++) cin >> tasks[i].second;
    sort(tasks.begin(), tasks.end());
    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto &t : tasks) {
        pq.push(t.second);
        if ((int)pq.size() > t.first) pq.pop();
    }
    long long ans = 0;
    while (!pq.empty()) { ans += pq.top(); pq.pop(); }
    cout << ans << "\n";
    return 0;
}
