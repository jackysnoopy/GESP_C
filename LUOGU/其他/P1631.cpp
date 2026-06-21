#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for (int i = 0; i < n; i++) pq.push({a[0] + b[i], 0});
    
    for (int i = 0; i < n; i++) {
        auto [sum, idx] = pq.top(); pq.pop();
        cout << sum << (i + 1 < n ? " " : "\n");
        if (idx + 1 < n) pq.push({a[idx+1] + sum - a[idx], idx + 1});
    }
    return 0;
}