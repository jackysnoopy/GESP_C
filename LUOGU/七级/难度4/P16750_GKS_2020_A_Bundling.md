# [GKS 2020 #A] Bundling

## 题目描述

Pip has $N$ strings. Each string consists only of letters from A to Z. Pip would like to bundle their strings into *groups* of size $K$. Each string must belong to exactly one group.

The score of a group is equal to the length of the longest prefix shared by all the strings in that group. For example:

*   The group {RAINBOW, RANK, RANDOM, RANK} has a score of $2$ (the longest prefix is 'RA').
*   The group {FIRE, FIREBALL, FIREFIGHTER} has a score of $4$ (the longest prefix is 'FIRE').
*   The group {ALLOCATION, PLATE, WORKOUT, BUNDLING} has a score of $0$ (the longest prefix is '').

Please help Pip bundle their strings into groups of size $K$, such that the sum of scores of the groups is maximized.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing the two integers $N$ and $K$. Then, $N$ lines follow, each containing one of Pip's strings.

## 输出格式

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum sum of scores possible.

## 样例

### 样例输入 1
```
2
2 2
KICK
START
8 2
G
G
GO
GO
GOO
GOO
GOOO
GOOO
```

### 样例输出 1
```
Case #1: 0
Case #2: 10
```

### 样例输入 2
```
1
6 3
RAINBOW
FIREBALL
RANK
RANDOM
FIREWALL
FIREFIGHTER
```

### 样例输出 2
```
Case #1: 6
```

## 提示

In Sample Case #1, Pip can achieve a total score of $0$ by making the groups:

*   $\{\text{KICK}, \text{START}\}$, with a score of $0$.

In Sample Case #2, Pip can achieve a total score of $10$ by making the groups:

*   $\{\text{G}, \text{G}\}$, with a score of $1$.
*   $\{\text{GO}, \text{GO}\}$, with a score of $2$.
*   $\{\text{GOO}, \text{GOO}\}$, with a score of $3$.
*   $\{\text{GOOO}, \text{GOOO}\}$, with a score of $4$.

### Limits

$1 \le T \le 100$.

$2 \le N \le 10^5$.

$2 \le K \le N$.

$K$ divides $N$.

Each of Pip's strings contain at least one character.

Each string consists only of letters from A to Z.

**Test Set 1**

Each of Pip's strings contain at most $5$ characters.

**Test Set 2**

The total number of characters in Pip's strings across all test cases is at most $2 \times 10^6$.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N, K;
        cin >> N >> K;

        vector<string> strings(N);
        for (int i = 0; i < N; i++) cin >> strings[i];

        sort(strings.begin(), strings.end());

        long long ans = 0;
        int count = 0;

        for (int i = 0; i < N; i++) {
            int common = 0;
            if (i > 0) {
                int j = i - 1;
                while (j >= 0 && count < K - 1) {
                    int len = min(strings[i].size(), strings[j].size());
                    int k = 0;
                    while (k < len && strings[i][k] == strings[j][k]) k++;
                    common = max(common, k);
                    j--;
                    count++;
                }
            }
            ans += common;
            if (count >= K - 1) count = 0;
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析

给定 $N$ 个字符串，需要将它们分成 $N/K$ 组，每组 $K$ 个字符串。每组的分数是所有字符串的最长公共前缀长度。求最大总分。

### 核心思路

贪心策略：将字符串排序后，相邻的字符串更可能有较长的公共前缀。

- 排序后，相邻字符串的公共前缀最长
- 每 $K$ 个字符串一组，取组内所有字符串的最长公共前缀
- 按排序顺序分组可以最大化总分

### 算法流程

1. 读入所有字符串并排序
2. 按顺序每 $K$ 个一组
3. 对每组，计算所有字符串的最长公共前缀
4. 累加所有组的分数

### 复杂度分析

- 时间复杂度：$O(N \cdot L \cdot \log N)$，其中 $L$ 是字符串平均长度
- 空间复杂度：$O(N \cdot L)$
