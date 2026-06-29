#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 300010;

int n, k;
int a[MAXN], l[MAXN], r[MAXN];
bool vis[MAXN];
long long ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    
    priority_queue<pair<int, int>> pq;
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        l[i] = i - 1;
        r[i] = i + 1;
        if (a[i] > 0) {
            pq.push({a[i], i});
        }
    }
    
    r[0] = 1;
    l[n + 1] = n;
    
    int cnt = 0;
    while (cnt < k && !pq.empty()) {
        int val = pq.top().first;
        int idx = pq.top().second;
        pq.pop();
        
        if (vis[idx]) continue;
        if (val <= 0) break;
        
        ans += val;
        vis[idx] = true;
        vis[l[idx]] = true;
        vis[r[idx]] = true;
        
        int new_val = a[l[idx]] + a[r[idx]] - a[idx];
        a[idx] = new_val;
        
        l[idx] = l[l[idx]];
        r[idx] = r[r[idx]];
        r[l[idx]] = idx;
        l[r[idx]] = idx;
        
        if (new_val > 0) {
            pq.push({new_val, idx});
        }
        
        cnt++;
    }
    
    cout << ans << "\n";
    return 0;
}