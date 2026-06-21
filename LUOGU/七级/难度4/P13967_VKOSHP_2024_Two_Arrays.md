# [VKOSHP 2024] Two Arrays

## 题目描述

Let the maximum in the array $d$ be denoted as $\max(d)$ and the minimum as $\min(d)$.

Two arrays $a$ and $b$ of length $n$ are given. In one operation, you can choose an index $1 \leq i \leq n$ and simultaneously increase the elements $a_i$ and $b_i$ by one: $a_i = a_i + 1$, $b_i = b_i + 1$. It is necessary to use these operations to achieve the simultaneous fulfillment of two conditions:

- $\max(a) - \min(a) \leq x$,
- $\max(b) - \min(b) \leq y$.

Determine the minimum number of operations required to achieve the simultaneous fulfillment of the specified conditions, or find out that it is impossible.

## 输入格式

Each test consists of several test cases. The first line contains one integer $t$ --- the number of test cases ($1 \leq t \leq 10^5$). The description of the test cases follows.

The first line of each test case contains three integers: $n$, $x$, $y$ ($1 \leq n \leq 10^5$, $0 \leq x, y \leq 10^9$).

The second line of each test case contains $n$ integers $a_1, a_2, \dots a_n$ --- the elements of array $a$ ($-10^9 \leq a_i \leq 10^9$).

The third line of each test case contains $n$ integers $b_1, b_2, \dots b_n$ --- the elements of array $b$ ($-10^9 \leq b_i \leq 10^9$).

It is guaranteed that the sum of $n$ across all test cases does not exceed $10^5$.

## 输出格式

For each test case, output one integer --- the minimum possible number of operations required to satisfy both conditions. If it is impossible to satisfy both conditions simultaneously, output $-1$.

## 样例

### 样例输入 1
```
5
4 2 3
-1 -2 -3 -4
-1 -2 -3 -4
3 3 2
1 6 4
1 4 1
4 0 3
0 2 1 2
0 2 3 3
5 2 1
-1 0 1 2 3
2 2 2 2 2
3 66 77
235 -111 9
100 -200 -100
```

### 样例输出 1
```
1
3
3
-1
440
```

## 提示

难度：普及+/提高

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
        int n, x, y;
        cin >> n >> x >> y;

        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        int min_a = *min_element(a.begin(), a.end());
        int max_a = *max_element(a.begin(), a.end());
        int min_b = *min_element(b.begin(), b.end());
        int max_b = *max_element(b.begin(), b.end());

        if (max_a - min_a > x || max_b - min_b > y) {
            cout << "-1\n";
            continue;
        }

        int ops = 0;
        for (int i = 0; i < n; i++) {
            int need_a = max(0, a[i] - min_a);
            int need_b = max(0, b[i] - min_b);
            ops = max(ops, max(need_a, need_b));
        }

        cout << ops << "\n";
    }

    return 0;
}
```
