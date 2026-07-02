#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
int n, q;
string S;
long long a[MAXN], w[MAXN];

int main() {
    scanf("%d", &n, &q);
    cin >> S;
    
    for (int i = 0; i <= n; i++) {
        scanf("%lld %lld", &a[i], &w[i]);
    }
    
    // 计算前缀和
    vector<long long> prefix_sum(n + 2, 0);
    for (int i = 0; i <= n; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + a[i];
    }
    
    long long total = prefix_sum[n + 1];
    
    // 对于每个询问，计算最小代价
    for (int i = 0; i <= q; i++) {
        long long ans = 1e18;
        
        // 尝试每个候选人
        for (int j = 0; j <= n; j++) {
            // 需要获得超过一半的票
            long long need = total / 2 + 1;
            
            // 计算当前候选人已经有的票
            long long have = a[j];
            
            // 如果票数足够，代价为0
            if (have >= need) {
                ans = min(ans, 0LL);
                continue;
            }
            
            // 否则需要揽票或投票
            long long cost = w[j];
            ans = min(ans, cost);
        }
        
        printf("%lld\n", ans);
        
        // 处理修改
        if (i < q) {
            int o, p;
            long long x;
            scanf("%d %d %lld", &o, &p, &x);
            
            if (o == 1) {
                total = total - a[p] + x;
                a[p] = x;
            } else {
                w[p] = x;
            }
        }
    }
    
    return 0;
}