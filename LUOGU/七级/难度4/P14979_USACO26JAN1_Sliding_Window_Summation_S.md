# [USACO26JAN1] Sliding Window Summation S

## 题目描述

Bessie 有一个隐藏的二进制字符串 $b_1b_2\dots b_N$（$1\le N\le 2\cdot 10^5$）。关于 $b$ 的唯一信息是一个二进制字符串 $r_1r_2\dots r_{N-K+1}$（$1 \le K \le N$），其中 $r_i$ 是 $b$ 中起始索引为 $i$、长度为 $K$ 的窗口内 $1$ 的个数除以 $2$ 的余数。

输出 Bessie 隐藏的二进制字符串中可能包含的 $1$ 的最小数量和最大数量。

## 输入格式

有 $T$（$1\le T\le 10^3$）个独立的测试用例需要解决。每个测试用例按以下格式指定：

第一行包含 $N$ 和 $K$。

第二行包含二进制字符串 $r_1\dots r_{N-K+1}$，其中 $r_i=\sum_{j=i}^{i+K-1}b_j\pmod{2}$。

保证所有测试用例的 $N$ 之和不超过 $10^6$。

## 输出格式

对于每个测试用例，输出 Bessie 隐藏的二进制字符串中可能包含的 $1$ 的最小数量和最大数量，用一个空格分隔。

## 样例

### 样例输入 1
```
7
5 1
10011
5 2
1001
5 3
100
5 5
0
5 5
1
4 4
1
5 2
0000
```

### 样例输出 1
```
3 3
2 3
1 4
0 4
1 5
1 3
0 5
```

## 提示

对于第一个测试用例，$K=1$ 意味着 $r=b$，而 $r$ 中 $1$ 的数量是 $3$。

对于第二个测试用例，$b$ 有两种可能性：10001 和 01110，分别有 $2$ 个和 $3$ 个 $1$。

---

- 输入 $2$：$N\le 8$
- 输入 $3$-$4$：$K\le 8$ 且所有测试用例的 $N$ 之和不超过 $10^4$。
- 输入 $5$-$11$：无额外约束。

翻译由 DeepSeek V3 完成

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

    while (T--) {
        int N, K;
        cin >> N >> K;

        string r;
        cin >> r;

        int len = r.size();
        int min_ones = 0, max_ones = 0;

        for (int i = 0; i < len; i++) {
            if (r[i] == '1') {
                min_ones++;
                max_ones++;
            }
        }

        cout << min_ones << " " << max_ones << "\n";
    }

    return 0;
}
```
