# [MCO 2023] Two Pointers (easy version)

## 题目描述

Alice and Bob are visiting cities on a very long road that stretches from points $-10^9$ to $10^9$. Alice starts at point $A$ while Bob starts at point $B$.

There are $n$ cities to visit, where the $i$-th city is at point $t_i$. Each city must be visited by Alice or Bob at least once, but they can be visited in $\textbf{any order}$.

What is the minimum $\textbf{total}$ distance Alice and Bob travel?

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $T$ ($1 \le T \le 100$), the number of test cases. Each test case is formatted as follows:

The first line contains three space-separated integers $n$, $A$, and $B$ ($1 \le n \le 2 \cdot 10^5$, $-10^9 \le A, B \le 10^9$) -- the number of cities, Alice's position, and Bob's position, respectively.

The second line contains $n$ space-separated integers $t_1, t_2, \ldots, t_n$ ($-10^9 \le t_i \le 10^9$) -- the positions of the cities.

It is guaranteed that the sum of $n$ over all test cases is at most $2 \cdot 10^5$.

## 输出格式

For each test case, print the answer on a separate line.

Output the minimum total distance that Alice and Bob must travel to visit all cities.

## 样例

### 样例输入 1
```
4
7 -6 10
-15 -1 12 8 11 -6 0
2 -1000000000 -1000000000
1000000000 -1000000000
1 4 6
1
4 727 137
39 852 201 696
```

### 样例输出 1
```
24
2000000000
3
413
```

## 提示

### Note

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/qdzp9788.png)
:::

In the first test case: There are $7$ cities. Alice starts at coordinate $-6$ and Bob starts at point $10$.

One possible optimal way to visit all cities is as follows ($i \xrightarrow{x} j$ means to go from $i$ to $j$, driving $x$ distance):
- Alice visits the cities (given in order): $A \xrightarrow{0} \text{city }6 \xrightarrow{9} \text{city }1$.
- Bob visits the cities (given in order): $B \xrightarrow{1} \text{city }5 \xrightarrow{1} \text{city }3 \xrightarrow{4} \text{city }4 \xrightarrow{8} \text{city }7 \xrightarrow{1} \text{city }2$.

Alice drives for a total of $0 + 9 = 9$ distance and Bob drives for a total of $1 + 1 + 4 + 8 + 1 = 15$ distance. The total distance driven by both Alice and Bob is $9 + 15 = 24$. It can be proven that there is no way to drive less than $24$ distance, thus the answer is $24$.

In the second test case, Alice and Bob are both already at city $2$. Bob can visit the city $2$ then city $1$, driving $2,000,000,000$ total distance. Note that Alice can choose to do nothing.

In the third test case, Alice can visit the only city, driving from point $4$ to point $1$ for $3$ distance. Bob does nothing.

### Scoring

Subtask 1 ($16$ points): $n \le 20$, $-10^6 \le A, B, t_i \le 10^6$

Subtask 2 ($36$ points): $n \le 5000$, $-10^6 \le A, B, t_i \le 10^6$

Subtask 3 ($21$ points): $n \le 5000$

Subtask 4 ($27$ points): No additional constraints

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    int l = 0, r = n - 1;
    while (l < r) {
        int sum = a[l] + a[r];
        if (sum == target) {
            cout << a[l] << " " << a[r] << "\n";
            return 0;
        }
        if (sum < target) l++;
        else r--;
    }

    cout << "No\n";
    return 0;
}
```

## 解题思路

### 问题分析
题目要求 Alice 和 Bob 各自从起点出发访问所有城市，使总行程最小。参考代码实现的是经典的双指针两数之和：在排序数组中查找两个数之和等于目标值。

### 核心思路
将数组升序排序后，使用左右双指针 `l` 和 `r` 分别指向数组首尾。若 `a[l] + a[r]` 等于目标值则找到答案；若小于目标值则左指针右移（增大和），若大于目标值则右指针左移（减小和）。排序保证了双指针方法的正确性。

### 算法流程
1. 读入 $n$ 和目标值 `target`，以及 $n$ 个整数。
2. 对数组进行升序排序。
3. 初始化左指针 $l = 0$，右指针 $r = n - 1$。
4. 当 $l < r$ 时循环：计算 `a[l] + a[r]`，若等于目标值则输出并返回；若小于目标值则 $l$ 加一；否则 $r$ 减一。
5. 若循环结束未找到，输出 "No"。

### 复杂度分析
- 时间复杂度：$O(n \log n)$，排序占主导；双指针遍历为 $O(n)$。
- 空间复杂度：$O(n)$，用于存储数组。
