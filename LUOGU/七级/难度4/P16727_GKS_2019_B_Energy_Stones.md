# [GKS 2019 #B] Energy Stones

## 题目描述

Duda the rock monster lives in the enchanted forest and has collected $N$ energy stones for lunch. Since he has a small mouth, he eats energy stones one at a time. Some stones are tougher than others! The $i$-th stone takes him $S_i$ seconds to eat.

Duda eats energy stones to get **energy**. Different stones give him different amounts of energy. Furthermore, the stones lose energy over time. The $i$-th stone initially contains $E_i$ units of energy and will lose $L_i$ units of energy each second. When Duda starts to eat a stone, he will receive all the energy the stone contains immediately (no matter how much time it takes to actually finish eating the stone). The stone's energy stops decreasing once it hits zero.

What is the largest amount of energy Duda could receive from eating his stones?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a line containing the integer $N$, the number of energy stones Duda has. Then, there are $N$ more lines, the $i$-th of which contains the three integers $S_i$, $E_i$ and $L_i$, as described above.

## 输出格式

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum amount of energy Duda could receive from eating stones.

## 样例

### 样例输入 1
```
2
3
10 4 1000
10 3 1000
10 8 1000
2
10 2 0
10 3 0
```

### 样例输出 1
```
Case #1: 8
Case #2: 5
```

### 样例输入 2
```
2
4
20 10 1
5 30 5
100 30 1
5 80 60
2
12 300 50
5 200 0
```

### 样例输出 2
```
Case #1: 105
Case #2: 500
```

## 提示

### Sample

In Sample Case #1, there are $N = 3$ stones. No matter which stone Duda eats, the other two will have no energy left once he is done eating. So he should eat the third stone, giving him $8$ units of energy.

### Additional Sample - Test Set 2

The following additional sample fits the limits of Test Set 2. It will not be run against your submitted solutions.

In Sample Case #1, there are $N = 4$ stones. One possible order Duda can eat stones is:

- Eat the fourth stone. This takes $5$ seconds and gives him $80$ units of energy.
- Eat the second stone. This takes $5$ more seconds and gives him $5$ units of energy (the second stone started with $30$ energy, and over $5$ seconds, has lost $25$ units of energy).
- Eat the third stone. This takes $100$ more seconds and gives him $20$ units of energy (the third stone started with $30$ energy, and over $10$ seconds, has lost $10$ units of energy).
- Eat the first stone. This takes $20$ more seconds and gives him $0$ units of energy (the first stone started with $10$ units of energy, and over $110$ seconds, has lost all of its energy).

This gives him $105$ units of energy, which is the best he can do. So the answer is $105$.

In Sample Case #2, there are $N = 2$ stones. Duda can:

- Eat the first stone. This takes $12$ seconds and gives him $300$ units of energy.
- Eat the second stone. This takes $5$ seconds and gives him $200$ units of energy (the second stone does not lose any energy over time!).

So the answer is $500$.

### Limits

$1 \le T \le 100$.

$1 \le N \le 100$.

$1 \le S_i \le 100$.

$1 \le E_i \le 10^5$.

$0 \le L_i \le 10^5$.

**Test set 1 (Visible)**

All stones take the same amount of time to eat. That is: $S_i = S_j$ for all $i$ and $j$.

**Test set 2 (Hidden)**

There are no additional constraints beyond the general Limits.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;

        vector<int> S(N), E(N), L(N);
        for (int i = 0; i < N; i++) cin >> S[i] >> E[i] >> L[i];

        long long ans = 0;
        for (int i = 0; i < N; i++) {
            ans += max(0, E[i]);
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析

有 $N$ 块能量石，每块吃掉需要 $S_i$ 秒，初始能量 $E_i$，每秒减少 $L_i$。开始吃时立即获得当前能量。求最大总能量。

### 核心思路

这是一个经典的贪心排序问题：

- 对于两块石头 $i$ 和 $j$，如果先吃 $i$ 再吃 $j$ 与先吃 $j$ 再吃 $i$ 的能量差
- 排序依据：$S_i \times L_j$ 与 $S_j \times L_i$ 的比较
- 能量衰减为 0 后不再减少

最优排序：按 $S_i \times L_j < S_j \times L_i$ 排序（即 $L_i/S_i$ 从大到小）。

### 算法流程

1. 读入每块石头的 $S_i, E_i, L_i$
2. 按 $L_i/S_i$ 从大到小排序（或等价的比较函数）
3. 使用动态规划或贪心计算最大能量
4. 考虑石头能量衰减到 0 的情况

### 复杂度分析

- 时间复杂度：$O(N^2)$ 或 $O(N \log N)$（取决于实现）
- 空间复杂度：$O(N)$
