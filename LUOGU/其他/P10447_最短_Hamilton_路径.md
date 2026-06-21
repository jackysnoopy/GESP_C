# 最短 Hamilton 路径

## 题目描述
给定一张 $n$ 个点的带权无向图，点从 $0 \sim n-1$ 标号，求起点 $0$ 到终点 $n-1$ 的最短 Hamilton 路径。 

Hamilton 路径的定义是从 $0$ 到 $n-1$ 不重不漏地经过每个点恰好一次。

## 输入格式
第一行输入整数 $n$。

接下来 $n$ 行每行 $n$ 个整数，其中第 $i$ 行第 $j$ 个整数表示点 $i-1$ 到 $j-1$ 的距离（记为 $a[i-1,j-1]$）。

对于任意的 $x,y,z$，数据保证 $a[x,x]=0，a[x,y]=a[y,x]$ 并且 $a[x,y]+a[y,z] \ge a[x,z]$。

## 输出格式
输出一个整数，表示最短 Hamilton 路径的长度。

## 样例
### 样例 1
```
5
0 2 4 5 1
2 0 6 5 3
4 6 0 8 3
5 5 8 0 5
1 3 3 5 0
```
```
18
```

## 提示
对于所有测试数据满足 $1 \le n \le 20$，$0 \le a[i,j] \le 10^7$

## 解题思路
### 问题分析
n 个点（n ≤ 20）的带权无向图，求从 0 到 n-1 的不重不漏经过每个点的最短 Hamilton 路径。

### 核心思路
状态压缩 DP。dp[mask][i] 表示当前已访问的点集为 mask，最后在点 i 时的最短路径长度。转移：从 i 走到 j。

### 算法流程
1. 读入 n 和邻接矩阵
2. 初始化 dp[1][0] = 0，其余为 INF
3. 枚举 mask，对每个 i 在集合中，尝试走到不在集合中的 j
4. dp[mask|1<<j][j] = min(dp[mask][i] + w[i][j])
5. 输出 dp[(1<<n)-1][n-1]

### 复杂度分析
- 时间复杂度：O(n² · 2^n)
- 空间复杂度：O(n · 2^n)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<vector<int>> w(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> w[i][j];
    
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX / 2));
    dp[1][0] = 0;
    
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask >> i & 1)) continue;
            for (int j = 0; j < n; j++) {
                if (mask >> j & 1) continue;
                int nmask = mask | (1 << j);
                dp[nmask][j] = min(dp[nmask][j], dp[mask][i] + w[i][j]);
            }
        }
    }
    
    cout << dp[(1 << n) - 1][n - 1] << "
";
    return 0;
}
```
