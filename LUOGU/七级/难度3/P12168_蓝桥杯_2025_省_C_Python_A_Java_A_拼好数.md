# [蓝桥杯 2025 省 C/Python A/Java A] 拼好数

## 题目描述

我们将含有不少于 $6$ 个 $6$ 的数视为一个好数。例如 $666666$、$162636465666$ 是好数，$12366666$ 不是好数。

给定 $n$ 个正整数 $a_i$，你可以把这些数分成若干组拼起来，每组内的数可以按任意顺序拼，但一组最多只能有 $3$ 个数。求最多可以得到多少个好数。

## 输入格式

输入的第一行包含一个正整数 $n$。

第二行包含 $n$ 个正整数 $a_1, a_2, \cdots, a_n$，相邻整数之间使用一个空格分隔。

## 输出格式

输出一行包含一个整数表示答案，即最多可以得到的好数的数量。

## 样例

### 样例输入 1
```
3
66 66 66
```

### 样例输出 1
```
1
```

### 样例输入 2
```
7
666666 16166 6696 666 6 6 6
```

### 样例输出 2
```
2
```

## 提示

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$1 \leq n \leq 20$；
- 对于所有评测用例，$1 \leq n \leq 1000$，$0 \leq a_i \leq 10^9$。

## 解题思路

### 问题分析
待补充

### 核心思路
待补充

### 算法流程
待补充

### 复杂度分析
待补充

## 参考代码

```cpp
#include <iostream>
#include <set>
using namespace std;
int count_sixes(long long x) {
    if (x == 0) return 0;
    int c = 0;
    while (x > 0) { if (x % 10 == 6) c++; x /= 10; }
    return c;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int big = 0;
    multiset<int> ms;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        int c = count_sixes(a);
        if (c >= 6) big++;
        else if (c > 0) ms.insert(c);
    }
    int groups = big;
    while (!ms.empty()) {
        auto it = prev(ms.end());
        int sum = *it;
        ms.erase(it);
        int used = 1;
        while (sum < 6 && used < 3 && !ms.empty()) {
            int need = 6 - sum;
            auto fit = ms.lower_bound(need);
            if (fit != ms.end()) { sum += *fit; ms.erase(fit); }
            else { auto lit = prev(ms.end()); sum += *lit; ms.erase(lit); }
            used++;
        }
        if (sum >= 6) groups++;
    }
    cout << groups << "\n";
    return 0;
}
```