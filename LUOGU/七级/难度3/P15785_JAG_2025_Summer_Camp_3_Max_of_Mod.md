# [JAG 2025 Summer Camp #3] Max of Mod

## 题目描述

You are given a set of integers $S = \{L, L+1, \ldots, R\}$. As long as $S$ does not contain $0$, you can repeatedly perform the following operation:

Choose a positive integer $g$ less than or equal to the maximum value in $S$, and replace each element of $S$ with its remainder when divided by $g$.

Determine the maximum number of operations that can be performed.

## 输入格式

The input consists of multiple test cases.

The first line contains an integer $T$ ($1 \leq T \leq 100\,000$), representing the number of test cases.

$T$ test cases follow. Each test case is given in the following format.

$$L \ R$$

For each test case, the only line contains integers $L$ and $R$ ($1 \leq L \leq R \leq 10^9$), representing the minimum and maximum values of the set, respectively.

## 输出格式

For the $T$ test cases, output the answers separated by newlines. For each test case, output the maximum number of operations that can be performed.

## 样例

### 样例输入 1
```
3
7 10
1 2718
20250913 20250915
```

### 样例输出 1
```
2
1
23
```

## 提示

难度：普及/提高−

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, mod;
    cin >> n >> mod;

    int maxMod = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        maxMod = max(maxMod, x % mod);
    }

    cout << maxMod << "\n";
    return 0;
}
```
