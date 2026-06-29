#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int n;
long long s[MAXN], a[MAXN];
long long pre[MAXN];
int ans[MAXN];

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) scanf("%lld", &s[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    
    // 计算前缀和
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
    
    // 计算每个位置的收益
    vector<pair<long long, int>> v;
    for (int i = 1; i <= n; i++) {
        v.push_back({2 * s[i] + a[i], i});
    }
    sort(v.begin(), v.end(), greater<pair<long long, int>>());
    
    // 使用优先队列维护最优选择
    priority_queue<int, vector<int>, greater<int>> pq;
    long long sum = 0;
    
    for (int i = 1; i <= n; i++) {
        int idx = v[i - 1].second;
        pq.push(idx);
        sum += a[idx];
        
        while ((int)pq.size() > i) {
            sum -= a[pq.top()];
            pq.pop();
        }
        
        int farthest = pq.top();
        ans[i] = 2 * s[farthest] + sum;
    }
    
    for (int i = 1; i <= n; i++) {
        printf("%lld\n", ans[i]);
    }
    
    return 0;
}
