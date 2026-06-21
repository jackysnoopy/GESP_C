#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Merge all numbers into one. Score when |m*x - y| condition met.
    // Use priority queue (min-heap) to greedily merge closest pairs.
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < n; i++) pq.push(a[i]);
    int score = 0;
    while (pq.size() > 1) {
        long long x = pq.top(); pq.pop();
        long long y = pq.top(); pq.pop();
        if (m * x >= y && m * y >= x) score++;
        pq.push(x + y);
    }
    cout << score << "\n";
    return 0;
}
