#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 305;
ll C[MAXN][MAXN];
int ans[MAXN];
bool used[MAXN];

int main() {
    int n;
    ll k, x;
    scanf("%d%lld%lld", &n, &k, &x);
    
    // 预处理组合数
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if (C[i][j] > k) C[i][j] = k + 1;
        }
    }
    
    int remaining_inv = x;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (used[j]) continue;
            
            // 如果选择j，会产生多少逆序对
            int inv_count = 0;
            for (int t = 1; t < j; t++) {
                if (!used[t]) inv_count++;
            }
            
            if (inv_count > remaining_inv) continue;
            
            // 计算剩余位置能产生的逆序对数
            ll ways = C[n - i][remaining_inv - inv_count];
            
            if (k <= ways) {
                ans[i] = j;
                used[j] = true;
                remaining_inv -= inv_count;
                break;
            } else {
                k -= ways;
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        printf("%d%c", ans[i], i == n ? '\n' : ' ');
    }
    
    return 0;
}
