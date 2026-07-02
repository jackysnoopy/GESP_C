# [USACO24OPEN] Cowreography G

## 题目描述

$N$ 头牛站成一排，每头牛是 Guernsey（0）或 Holstein（1）。每次操作可以交换距离不超过 $K$ 的两头牛。给定初始和最终的二进制串，求最少交换次数。

## 输入格式

第一行包含 $N$ 和 $K$。第二行初始二进制串，第三行最终二进制串。保证两个串中 1 的数量相同。

## 输出格式

一个整数，表示最少交换次数。

## 样例

**输入 1：**
```
4 1
0111
1110
```
**输出 1：**
```
3
```

**输入 2：**
```
5 2
11000
00011
```
**输出 2：**
```
6
```

**输入 3：**
```
5 4
11000
00011
```
**输出 3：**
```
2
```

## 提示

- 对于样例 1（$K=1$）：$0111 \to 1011 \to 1101 \to 1110$，3 步。
- 对于样例 3（$K=4$）：$11000 \to 10010 \to 00011$，2 步。
- 评分：输入 4-5 为 $K=1$，输入 6-7 最多 8 个 1，输入 8-15 为 $N\le5000$，输入 16-23 无额外约束。

## 解题思路

### 问题分析

每次交换可以将一头牛移动最多 $K$ 个位置。我们需要将初始排列变为目标排列。

### 核心思路

1. 提取初始和最终串中 '1' 的位置，分别记为 $P$ 和 $Q$。
2. 按顺序一一配对：第 $i$ 个 1 从位置 $P_i$ 移到位置 $Q_i$。
3. 每次交换最多让一头 1 移动 $K$ 步，因此每对 $(P_i, Q_i)$ 需要 $\lceil |P_i - Q_i| / K \rceil$ 次交换。
4. 答案为所有配对的距离之和除以 $K$ 上取整。

### 算法流程

1. 读入初始串和目标串。
2. 提取两个串中 '1' 的位置。
3. 计算配对距离之和 $D = \sum |P_i - Q_i|$。
4. 输出 $\lceil D / K \rceil = (D + K - 1) / K$。

### 复杂度分析

- 时间复杂度：$O(N)$
- 空间复杂度：$O(N)$

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll k;
    cin >> n >> k;
    string a, b;
    cin >> a >> b;

    vector<ll> pa, pb;
    for (int i = 0; i < n; i++) {
        if (a[i] == '1') pa.push_back(i);
        if (b[i] == '1') pb.push_back(i);
    }

    ll totalDist = 0;
    for (int i = 0; i < (int)pa.size(); i++) {
        totalDist += abs(pa[i] - pb[i]);
    }

    ll ans = (totalDist + k - 1) / k;
    cout << ans << "\n";
    return 0;
}
```
