#include <iostream>
#include <stack>
using namespace std;

const int N = 205;
long long a[N][N];
long long col[N][N]; // 列前缀
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) cin >> a[i][j];
    // 列前缀和
    for (int j = 1; j <= m; ++j)
        for (int i = 1; i <= n; ++i)
            col[i][j] = col[i-1][j] + a[i][j];
    int ans = 0;
    // 枚举上下行
    for (int u = 1; u <= n; ++u) {
        for (int d = u; d <= n; ++d) {
            int height = d - u + 1;
            // 一维问题：最大子段和 >= 0 的最长子段
            // s[j] = col[d][j] - col[u-1][j] (该列在 [u,d] 行内的和)
            // 求最长 j1..j2 使得 sum(s[j1..j2]) >= 0 → 最长子区间使前缀和 P[j2] >= P[j1-1]
            // 经典 O(M) 单调栈：
            static long long P[N];
            P[0] = 0;
            for (int j = 1; j <= m; ++j) P[j] = P[j-1] + (col[d][j] - col[u-1][j]);
            // 最长 (l,r) with P[r] >= P[l], 答案 r - l 列宽
            // 单调栈：存递减 P 的下标
            static int stk[N];
            int top = 0;
            stk[top] = 0;
            for (int j = 1; j <= m; ++j) {
                if (P[j] < P[stk[top]]) stk[++top] = j;
            }
            // 从右往左扫
            for (int j = m; j >= 1; --j) {
                while (top >= 0 && P[j] >= P[stk[top]]) {
                    int width = j - stk[top];
                    long long area = (long long)width * height;
                    if (area > ans) ans = (int)area;
                    --top;
                }
                if (top < 0) break;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
