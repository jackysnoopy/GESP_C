# 【MX-X26-T3】「Cfz Round 7」GLACIES

## 题目描述

愛してる過去の夜も　/　深爱着的过去的夜晚

今じゃ季節に煌めいてゆく　/　如今也在时光里闪闪发亮

Yuki 有一个长度为 $n$ 的序列 $a$ 和一个正整数 $m$。保证对于所有 $1 \le i \le n$，均有 $0 \le a_i \lt 2^m$。

对于序列 $a$，Yuki 定义其「鱼鱼值」等于：

$$
a_1 \text{ and } a_2 \text{ and } \cdots \text{ and } a_n
$$

即序列 $a$ 中的所有数按位与得到的结果。

Yuki 定义一次「大了」操作为：

- 选择一个不大于 $n$ 的正整数 $i$，将 $a_i$ 的值修改为 $(2 \cdot a_i) \bmod 2^m$。

Yuki 希望进行若干次「大了」操作（可以为 $0$ 次），使序列 $a$ 的「鱼鱼值」尽可能大。

你需要帮助她求出，使序列 $a$ 的「鱼鱼值」达到最大值所需的「大了」操作次数的最小值。

## 输入格式

**本题有多组测试数据。**

输入的第一行包含两个整数 $c,t$，分别表示该测试点所属的子任务编号和测试数据组数。样例满足 $c=0$。

接下来依次输入每组测试数据。对于每组测试数据：

- 第一行包含两个整数 $n,m$。
- 第二行包含 $n$ 个整数 $a_1,\dots,a_n$。

## 输出格式

对于每组测试数据，输出一行，包含一个整数，表示使序列 $a$ 的「鱼鱼值」达到最大值所需的「大了」操作次数的最小值。

## 样例

### 样例输入 1
```
0 4
3 4
1 3 8
2 3
4 0
3 5
3 6 11
3 4
5 7 13
```

### 样例输出 1
```
5
0
8
3
```

## 提示

### 样例 1 解释

对于第 $1$ 组测试数据，可以选择 $i=1$ 进行 $3$ 次「大了」操作，再选择 $i=2$ 进行 $2$ 次「大了」操作，使序列 $a$ 变为 $\{8,12,8\}$，「鱼鱼值」等于 $8$。可以证明序列 $a$ 的「鱼鱼值」所能达到的最大值即为 $8$，且至少需要进行 $5$ 次操作。

对于第 $2$ 组测试数据，无论怎么操作，序列 $a$ 的「鱼鱼值」都为 $0$，因此答案为 $0$。

### 数据范围

设 $\sum n$ 表示单个测试点中 $n$ 的和。

对于所有测试数据，均有：

- $1 \le t \le 5\cdot10^5$；
- $1 \le n \le 5\cdot 10^5$，$1 \le m \le 60$，$\sum n \le 5\cdot10^5$；
- 对于所有 $1 \le i \le n$，均有 $0 \le a_i \lt 2^m$。

**本题采用捆绑测试。**

- Subtask 1（15 points）：$n,m \le 8$，$\sum n \le 8$。
- Subtask 2（18 points）：$n \le 10^3$，$m \le 10$，$\sum n \le 10^3$。
- Subtask 3（21 points）：$n \le 10^4$，$m \le 20$，$\sum n \le 10^4$。
- Subtask 4（21 points）：$n \le 10^5$，$m \le 30$，$\sum n \le 10^5$。
- Subtask 5（25 points）：无特殊限制。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, t;
    cin >> c >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans |= a[i];
        }

        cout << ans << "\n";
    }

    return 0;
}
```
