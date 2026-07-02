# [GCJ 2015 #3] Smoothing Window

## 题目描述

给定 N 个整数的滑动窗口和（窗口大小 K），求原始序列 max(x)-min(x) 的最小可能值。

## 输入格式

第一行 T，每组包含 N、K 和 N-K+1 个整数 sum[i]（sum[i] = K × s[i]）。

## 输出格式

Case #x: y，y 为最小可能的差值。

## 样例

```
3
10 2
1 2 3 4 5 6 7 8 9
100 100
-100
7 3
0 12 0 12 0
```

输出：
```
Case #1: 5
Case #2: 0
Case #3: 12
```

## 解题思路

### 问题分析
核心约束：sum[i+1] - sum[i] = x[i+K] - x[i]。同一余数类中的元素形成链。

### 核心思路
- K=1 时，每个元素独立，答案为 max(sum) - min(sum)
- K≥2 时，对每个余数类 r (0≤r<K)，链中相邻元素差值固定。计算每个链的范围 R_r = max - min
- 答案 = max(max_r(R_r), ceil((S%K + ΣR_r) / K))

### 算法流程
1. 对 K=1 特判
2. 对每个余数类计算差分链的范围
3. 合并得到答案

### 复杂度分析
- 时间：O(N)
- 空间：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int N, K; cin >> N >> K;
        int m = N - K + 1;
        vector<long long> sum(m);
        for (int i = 0; i < m; i++) cin >> sum[i];
        cout << "Case #" << t << ": ";
        if (K == 1) {
            long long mn = sum[0], mx = sum[0];
            for (int i = 1; i < m; i++) { mn = min(mn, sum[i]); mx = max(mx, sum[i]); }
            cout << mx - mn << "\n"; continue;
        }
        long long maxR = 0, sumR = 0, sumMin = 0;
        for (int r = 0; r < K; r++) {
            long long d = 0, dMin = 0, dMax = 0;
            for (int j = 0; r + j*K + 1 <= N-K; j++) {
                d += sum[r + j*K + 1] - sum[r + j*K];
                dMin = min(dMin, d); dMax = max(dMax, d);
            }
            maxR = max(maxR, dMax - dMin);
            sumR += dMax - dMin; sumMin += dMin;
        }
        long long S = sum[0] + sumMin;
        long long rMod = ((S % K) + K) % K;
        cout << max(maxR, (rMod + sumR + K - 1) / K) << "\n";
    }
    return 0;
}
```
