# [USACO26JAN2] Farmer John Loves Rotations S

## 题目描述

Farmer John has an array $A$ containing $N$ integers ($1 \leq N \leq 5 \cdot 10^5, 1 \leq A_i \leq N$). He picks his favorite index $j$ and take out a sheet of paper with only $A_j$ written on it. He can then perform the following operation some number of times:

- Cyclically shift all elements in $A$ one spot to the left or one spot to the right. Then, write down $A_j$ on a piece of paper.

Let $S$ denote the set of distinct integers that occur in $A$. Farmer John wonders what the minimum number of operations he must perform is so that the paper contains all integers that appear in $S$.

Since it is unclear what FJ's favorite index is, output the answer for all possible favorite indices $1 \leq j \leq N$. Note for each index, $A$ is reset to its original form before performing any operations.

## 输入格式

The first line contains $N$.

The following line contains $A_1, A_2, \ldots, A_N$.

## 输出格式

Output $N$ space-separated integers, where the $i$'th integer is the answer for his favorite index $j = i$.

## 样例

### 样例输入 1
```
6
1 2 3 1 3 4
```

### 样例输出 1
```
4 3 3 4 3 3
```

### 样例输入 2
```
12
1 1 2 1 1 3 1 1 4 1 1 1
```

### 样例输出 2
```
8 7 6 7 8 9 8 7 6 7 8 9
```

## 提示

#### Sample 1 Explanation

The distinct numbers are $S = \{ 1, 2, 3, 4 \}$. Suppose Farmer John’s favorite index is $j=1$. He starts off with $A_1=1$ written on a piece of paper. We can track the array $A$ after each cyclic shift Farmer John makes.
- Cyclic shift right: FJ writes down $A_1 = 4$.
:::align{center}
 4 1 2 3 1 3
:::
- Cyclic shift left: FJ writes down $A_1 = 1$ again.
:::align{center}
 1 2 3 1 3 4
:::
- Cyclic shift left: FJ writes down $A_1 = 2$.
:::align{center}
 2 3 1 3 4 1
:::
- Cyclic shift left: FJ writes down $A_1 = 3$.
:::align{center}
 3 1 3 4 1 2
:::
At this point, Farmer John has written down every number in $S$ using 4 operations.

SCORING:
- Inputs 3-5: $N\le 500$
- Inputs 6-8: $N\le 10^4$
- Inputs 9-17: No additional constraints.

## 解题思路

### 问题分析
给定数组 A 和索引 j，初始纸上写有 A[j]。每次可以循环左移或右移数组，然后将 A[j] 写在纸上。求收集齐所有不同元素的最少操作次数。对每个 j 都要求答案。

### 核心思路
模拟：对每个起始位置 j，不断向右遍历数组（循环），将 A[cur] 加入集合，直到集合包含所有不同元素。记录步数即可。

### 算法流程
1. 计算数组中不同元素的总数 distinct
2. 对每个索引 j：
   - 初始化 seen 为空集合，ops = 0，cur = j
   - 循环：将 A[cur] 加入 seen，ops++，cur = (cur+1) % N
   - 直到 seen.size() == distinct
   - 记录 ans[j] = ops
3. 输出所有答案

### 复杂度分析
- 时间复杂度：O(N²)，对每个 j 最多遍历 N 个元素
- 空间复杂度：O(N)，存储答案和集合

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    set<int> S(A.begin(), A.end());
    int distinct = S.size();

    vector<int> ans(N);

    for (int j = 0; j < N; j++) {
        set<int> seen;
        int ops = 0;
        int cur = j;

        while (seen.size() < distinct) {
            seen.insert(A[cur]);
            ops++;
            cur = (cur + 1) % N;
        }

        ans[j] = ops;
    }

    for (int i = 0; i < N; i++) {
        if (i) cout << " ";
        cout << ans[i];
    }
    cout << "\n";

    return 0;
}
```

## 解题思路

### 问题分析
数组A可以循环移位，每次移位后记录A[j]的值。需要找到从每个位置j开始，最少多少次移位能收集到数组中所有不同的数。

### 核心思路
对于每个起始位置j，模拟向右遍历数组（循环），直到收集到所有不同的数。使用set记录已见过的数。

### 算法流程
1. 统计数组中不同元素的数量
2. 对每个起始位置j：
   - 从j开始向右遍历
   - 将经过的元素加入seen集合
   - 当seen大小等于不同元素总数时停止
   - 记录操作次数
3. 输出所有位置的答案

### 复杂度分析
- 时间复杂度：O(N²)，每个位置可能遍历整个数组
- 空间复杂度：O(N)
