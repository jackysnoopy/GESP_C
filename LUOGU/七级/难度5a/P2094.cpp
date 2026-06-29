#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    priority_queue<double> pq;
    for (int i = 0; i < n; i++) {
        double w;
        cin >> w;
        pq.push(w);
    }
    
    while (pq.size() > 1) {
        double a = pq.top(); pq.pop();
        double b = pq.top(); pq.pop();
        pq.push((a + b) / k);
    }
    
    int ans = (int)pq.top();
    cout << ans << "\n";
    return 0;
}