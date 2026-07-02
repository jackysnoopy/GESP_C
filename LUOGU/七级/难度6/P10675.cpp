#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;
const int MOD = 998244353;
int n, q;
int a[MAXN];

int main() {
    scanf("%d %d", &n, &q);
    
    // 统计每个幂次的出现次数
    vector<int> cnt(MAXN, 0);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (a[i] < MAXN) cnt[a[i]]++;
    }
    
    for (int i = 0; i < q; i++) {
        int m;
        scanf("%d", &m);
        
        vector<int> p(m);
        for (int j = 0; j < m; j++) {
            scanf("%d", &p[j]);
        }
        
        if (m == 0) {
            printf("0\n");
            continue;
        }
        
        // 贪心：从高位向低位考虑
        long long ans = 0;
        bool possible = true;
        vector<int> have = cnt;
        
        for (int j = 0; j < m && possible; j++) {
            int bit = p[j];
            
            // 尝试用已有的2^bit来满足
            if (have[bit] > 0) {
                have[bit]--;
                ans = (ans + (1LL << bit)) % MOD;
            } else {
                // 需要从更高位借位
                bool found = false;
                for (int k = bit + 1; k < MAXN; k++) {
                    if (have[k] > 0) {
                        have[k]--;
                        // 分解为2个2^(k-1)
                        for (int l = k - 1; l > bit; l--) {
                            have[l] += 2;
                        }
                        have[bit] += 2;
                        have[bit]--;
                        ans = (ans + (1LL << bit)) % MOD;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    possible = false;
                }
            }
        }
        
        if (!possible) {
            printf("-1\n");
        } else {
            printf("%lld\n", ans);
        }
    }
    
    return 0;
}