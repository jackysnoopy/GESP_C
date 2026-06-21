#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    
    vector<long long> d(n - 1);
    for (int i = 0; i < n - 1; i++) d[i] = x[i+1] - x[i];
    
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    for (int i = 0; i < n - 1; i++) pq.push({d[i], i});
    
    vector<int> L(n - 1), R(n - 1);
    for (int i = 0; i < n - 1; i++) L[i] = i - 1, R[i] = i + 1;
    R[n-2] = -1;
    
    vector<bool> del(n - 1, false);
    long long ans = 0;
    
    while (k--) {
        while (del[pq.top().second]) pq.pop();
        auto [val, idx] = pq.top(); pq.pop();
        ans += val;
        
        int l = L[idx], r = R[idx];
        if (l != -1) del[l] = true;
        if (r != -1) del[r] = true;
        
        if (l != -1 && r != -1) {
            d[idx] = d[l] + d[r] - d[idx];
            pq.push({d[idx], idx});
            L[idx] = L[l]; 
            if (L[l] != -1) R[L[l]] = idx;
            R[idx] = R[r];
            if (R[r] != -1) L[R[r]] = idx;
        } else {
            del[idx] = true;
        }
    }
    
    cout << ans << "\n";
    return 0;
}