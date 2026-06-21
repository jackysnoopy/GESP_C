# [UOI 2021 II Stage] 字典序

## 题目描述

最近有人送给哥萨克一个包含 $n$ 个整数的数组 $a$。

胡子立刻想要对数组的元素进行排序，使得排序后数组中任意两个相邻的数字都不相同。在所有这样的排序中，他想找到字典序最小的那个。

回忆一下，字典序定义如下。假设有两个数组。找到第一个两个数组元素不同的位置。如果在该位置第一个数组的元素小于第二个数组的元素，则第一个数组字典序小于第二个数组；否则，第一个数组字典序大于第二个数组。例如，以下不等式成立：$[10, 3, 1] < [10, 4, 5]$, $[1, 1, 1] < [1, 2, 3]$, $[1, 2, 3] < [10, 10, 10]$。

## 输入格式

第一行包含一个整数 $n$ $(1 \leq n \leq 5 \cdot 10^5)$ —— 数组的元素个数。

第二行包含 $n$ 个整数 $a_1, a_2, ..., a_n$ $(1 \leq a_i \leq 5 \cdot 10^5)$ —— 数组的元素。

## 输出格式

如果无法对哥萨克的数组进行排序，则输出单个数字 $-1$。

否则，输出 $n$ 个整数 —— 哥萨克的数组的字典序最小排序。

## 样例

### 样例输入 1
```
5
3 1 2 3 3
```

### 样例输出 1
```
3 1 3 2 3
```

### 样例输入 2
```
6
2 3 1 1 2 4
```

### 样例输出 2
```
1 2 1 2 3 4
```

### 样例输入 3
```
4
1 2 1 1
```

### 样例输出 3
```
-1
```

## 提示

### 样例说明

在第一个样例中，存在唯一的排序。

在第二个样例中，还存在其他排序，例如：$[1, 2, 3, 4, 1, 2]$ 或 $[1, 4, 1, 2, 3, 2]$。但所有这些排序在字典序上都大于 $[1, 2, 1, 2, 3, 4]$。

在第三个样例中，不存在有效的排序（数组中总会有两个 $1$ 出现在相邻位置）。

### 评分细则

本题采用 **按测试点** 评分。一些额外的限制条件：

-   （5 分）： $n \leq 10^3, a_i \leq 2$
-   （10 分）： $n \leq 10^3, a_i \leq 3$
-   （25 分）： $n \leq 10^3, a_i \leq 5 \cdot 10^5$
-   （5 分）： $n \leq 5 \cdot 10^5, a_i \leq 2$
-   （10 分）： $n \leq 5 \cdot 10^5, a_i \leq 3$
-   （45 分）： $n \leq 5 \cdot 10^5, a_i \leq 5 \cdot 10^5$

翻译由 DeepSeek V3 完成

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> count(n + 1, 0);
    for (int x : a) count[x]++;

    int max_count = *max_element(count.begin(), count.end());
    if (max_count > (n + 1) / 2) {
        cout << -1 << "\n";
        return 0;
    }

    priority_queue<pair<int, int>> pq;
    for (int i = 1; i <= n; i++) {
        if (count[i] > 0) pq.push({count[i], i});
    }

    vector<int> result;
    int prev = -1;

    while (!pq.empty()) {
        auto [cnt1, val1] = pq.top();
        pq.pop();

        if (val1 != prev) {
            result.push_back(val1);
            prev = val1;
            if (cnt1 > 1) pq.push({cnt1 - 1, val1});
        } else {
            if (pq.empty()) {
                cout << -1 << "\n";
                return 0;
            }
            auto [cnt2, val2] = pq.top();
            pq.pop();
            result.push_back(val2);
            prev = val2;
            if (cnt1 > 0) pq.push({cnt1, val1});
            if (cnt2 > 1) pq.push({cnt2 - 1, val2});
        }
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << result[i];
    }
    cout << "\n";

    return 0;
}
```
