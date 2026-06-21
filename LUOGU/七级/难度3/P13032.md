# [GCJ 2021 #1C] Closest Pick

## 题目描述

抽奖：已有 $N$ 张售出的票，每张票上有一个 $1$ 到 $K$ 的整数。你是最后一位顾客，可以购买两张票（两数可相同，自选 $1$ 到 $K$ 内的整数）。随后随机均匀地选一个整数 $c \in [1,K]$。若你的某张票到 $c$ 的距离**严格小于**所有已售票到 $c$ 的距离，或你的两张票到 $c$ 距离相等且都严格小于所有已售票的距离，则你赢。

求最优选择两张票时能获得的最大获胜概率。

## 输入格式

第一行 $T$。每组数据两行：第一行 $N, K$；第二行 $N$ 个整数 $P_i$（已售票上的数）。

## 输出格式

对每组数据输出 `Case #x: y`，$y$ 为最大获胜概率，绝对/相对误差 $10^{-6}$ 内即算正确。

## 提示

**样例说明**：Case 1 选 $4,8$（或 $6,8$）可赢 $5$ 个 $c$，概率 $0.5$；Case 3 每个 $c$ 都紧贴某张已售票，无法赢，概率 $0$。

**数据范围**：$1 \le T \le 100$，$1 \le N \le 30$，$1 \le P_i \le K$，$1 \le K \le 10^9$（Test Set 2）。

时间限制 1000ms，内存限制 1GB。

## 解题思路

### 问题分析

获胜条件等价于：$\min(|c-a|,|c-b|) < \min_{p\in S}|c-p|$，其中 $a,b$ 是你的两张票，$S$ 是已售票集合（去重）。即你的最近票比所有已售票都更靠近 $c$。已售票把 $[1,K]$ 切成若干"空隙"，你只能在空隙中放置票来覆盖 $c$。

### 核心思路

**单张票覆盖力**：
- 边界空隙（$[1, P_{(1)}-1]$ 或 $[P_{(m)}+1, K]$）：在空隙内放一张票即可覆盖**整个**空隙（你对所有这些 $c$ 都比最近的已售票更近）。覆盖数 = 空隙长度。
- 内部空隙（相邻 $P_i, P_{i+1}$，差 $d$）：放一张票于中间，覆盖严格比两端都近的整数，共 $\lfloor d/2\rfloor$ 个。

**两张票两种策略取最优**：
1. **分开放**：两张票放进两个不同空隙，各取其单票覆盖，总和最大 → 取最大的两个单票覆盖之和。
2. **集中放**：两张票放进同一个内部空隙的两端（$P_i+1$ 与 $P_{i+1}-1$），可覆盖该空隙全部内部整数 $d-1$ 个（边界空隙集中放仍是其长度，无额外收益）。取所有空隙"双票集中覆盖"的最大值。

答案 $= \max(\text{两个最大单票覆盖之和},\; \text{最大双票集中覆盖})$，概率 $= \text{答案}/K$。

**特例**：仅 1 张已售票时覆盖 $K-1$（除该位置外都能赢）；无已售票时覆盖 $K$（概率 1）。

### 算法流程

1. 读入 $P$，排序去重，$m$ 为不同值个数。
2. $m=0$ 输出 1；$m=1$ 输出 $(K-1)/K$。
3. 收集单票覆盖 `gaps`：左边界 $P_0-1$、右边界 $K-P_{m-1}$、各内部 $\lfloor d/2\rfloor$。降序排序。
4. `split = gaps[0] + gaps[1]`（两个最大之和）。
5. `concentrate = max(左边界, 右边界, 各内部 d-1)`。
6. `best = max(split, concentrate)`，输出 `best/K`。

### 复杂度分析

- 时间复杂度：$O(N\log N)$（排序）。
- 空间复杂度：$O(N)$。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N, K;
        cin >> N >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        sort(P.begin(), P.end());
        P.erase(unique(P.begin(), P.end()), P.end());
        int m = P.size();
        vector<int> gaps;
        if (m == 0) {
            cout << "Case #" << tc << ": " << fixed << setprecision(9) << 1.0 << "\n";
            continue;
        }
        if (m == 1) {
            int cov = K - 1;
            cout << "Case #" << tc << ": " << fixed << setprecision(9) << (double)cov / K << "\n";
            continue;
        }
        gaps.push_back(P[0] - 1);
        gaps.push_back(K - P[m-1]);
        for (int i = 0; i + 1 < m; i++)
            gaps.push_back((P[i+1] - P[i]) / 2);
        sort(gaps.rbegin(), gaps.rend());
        int best = max(gaps[0], (m >= 2 ? (gaps[0] + (gaps.size() > 1 ? gaps[1] : 0)) : gaps[0]));
        // Also consider full gap (two tickets in same gap)
        int fullGap = P[0] - 1;
        fullGap = max(fullGap, K - P[m-1]);
        for (int i = 0; i + 1 < m; i++)
            fullGap = max(fullGap, P[i+1] - P[i] - 1);
        best = max(best, fullGap);
        // Also: two largest one-ticket coverages
        int sum2 = gaps[0];
        if (gaps.size() > 1) sum2 += gaps[1];
        best = max(best, sum2);
        cout << "Case #" << tc << ": " << fixed << setprecision(9) << (double)best / K << "\n";
    }
    return 0;
}
```
