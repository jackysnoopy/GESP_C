#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e6 + 10;
const long long INF = 1e18;

int n, k;
long long a[MAXN];
long long dp[2][MAXN]; // 滚动数组，dp[j]表示选j个子段的最大和
long long pre[MAXN];   // pre[j] = max(dp[j-1], pre[j-1])，用于转移

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);

    int cur = 0;
    // 初始化dp为负无穷
    for (int j = 0; j <= k; j++)
        dp[cur][j] = -INF;
    dp[cur][0] = 0;

    for (int i = 1; i <= n; i++) {
        int nxt = cur ^ 1;
        // 初始化新一层
        for (int j = 0; j <= k; j++)
            dp[nxt][j] = -INF;
        dp[nxt][0] = 0;

        // pre[j] 表示从 dp[cur][0..j-1] 转移来的最大值（开启新段）
        pre[0] = -INF;
        for (int j = 1; j <= k; j++)
            pre[j] = max(pre[j - 1], dp[cur][j - 1]);

        for (int j = 1; j <= k; j++) {
            // 转移1：不选a[i]
            dp[nxt][j] = dp[cur][j];
            // 转移2：以a[i]开启新子段
            dp[nxt][j] = max(dp[nxt][j], pre[j] + a[i]);
            // 转移3：将a[i]接到上一个子段末尾
            dp[nxt][j] = max(dp[nxt][j], dp[cur][j] + a[i]);
        }

        cur = nxt;
    }

    printf("%lld\n", dp[cur][k]);
    return 0;
}
