#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250005;
int n;
long long a[MAXN], b[MAXN];
int ans[MAXN];

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
    
    priority_queue<pair<long long, int>> pq; // (b[i], i)
    long long stock = 0;
    int cnt = 0;
    
    for (int i = 1; i <= n; i++) {
        stock += a[i];
        pq.push({b[i], i});
        
        if (stock >= b[i]) {
            stock -= b[i];
            ans[++cnt] = i;
        } else {
            // 替换一个更大的
            if (!pq.empty() && pq.top().first > b[i]) {
                auto [val, idx] = pq.top();
                pq.pop();
                stock += val - b[i];
                ans[cnt] = i;
            } else {
                pq.pop();
            }
        }
    }
    
    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; i++) {
        printf("%d%c", ans[i], i == cnt ? '\n' : ' ');
    }
    
    return 0;
}
