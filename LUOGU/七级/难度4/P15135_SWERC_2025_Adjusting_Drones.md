# [SWERC 2025] Adjusting Drones

## 题目描述

You are managing a fleet of $n$ drones, each with an energy level $a_1, \dots, a_n$. You are also given a positive integer $k$, which represents the maximum number of drones allowed to share the same energy level.

To prevent overloads, the drones automatically perform energy balancing operations as follows. While there exists an energy level that appears strictly more than $k$ times, they execute the following steps:

- first, every drone $i$ whose energy $a_i$ has already appeared before (that is, there exists $j < i$ with $a_j = a_i$) is marked;
- then, for each marked drone, its energy is increased by 1 unit;
- then, the marks are removed.

The process stops once no energy level appears more than $k$ times. Determine how many energy balancing operations will be performed.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.

The first line of each test case contains two integers $n, k$ ($1 \le k \le n \le 2 \cdot 10^5$) — the number of drones and the maximum allowed number of drones with the same energy level.

The second line of each test case contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le 2n$) — the initial energy levels of the drones.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

## 输出格式

For each test case, output a single line containing an integer: the number of energy balancing operations performed.

## 样例

### 样例输入 1
```
5
6 3
1 1 1 1 1 1
5 1
1 3 2 1 4
16 2
6 3 7 5 13 6 7 6 3 5 13 7 6 4 3 6
16 3
6 3 7 5 13 6 7 6 3 5 13 7 6 4 3 6
16 4
6 3 7 5 13 6 7 6 3 5 13 7 6 4 3 6
```

### 样例输出 1
```
3
4
14
5
4
```

## 提示

### Explanation of sample 1.

In the first test case, the drones’ energy levels evolve as follows:

- at the beginning, $[1, 1, 1, 1, 1, 1]$;
- after 1 operation, $[1, 2, 2, 2, 2, 2]$;
- after 2 operations, $[1, 2, 3, 3, 3, 3]$;
- after 3 operations, $[1, 2, 3, 4, 4, 4]$.

After 3 operations, every energy level appears at most 3 times, so the process stops.

In the second test case, the energy levels change as follows: $[1, 3, 2, 1, 4] \to [1, 3, 2, 2, 4] \to [1, 3, 2, 3, 4] \to [1, 3, 2, 4, 4] \to [1, 3, 2, 4, 5]$. The process stops after 4 operations.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> count(2 * n + 1, 0);
    int ops = 0;

    for (int i = 0; i < n; i++) {
        count[a[i]]++;
        if (count[a[i]] > k) {
            ops++;
            count[a[i]]--;
            count[a[i] + 1]++;
        }
    }

    cout << ops << "\n";
    return 0;
}
```
