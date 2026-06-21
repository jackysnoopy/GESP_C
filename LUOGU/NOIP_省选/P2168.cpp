#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < n; i++) {
        long long x; cin >> x;
        pq.push(x);
    }
    
    // 补0使满足 (n-1)%(k-1)==0
    while ((pq.size() - 1) % (k - 1) != 0)
        pq.push(0);
    
    long long ans = 0;
    while (pq.size() > 1) {
        long long sum = 0;
        for (int i = 0; i < k; i++) {
            sum += pq.top(); pq.pop();
        }
        ans += sum;
        pq.push(sum);
    }
    
    cout << ans << "\n";
    return 0;
}