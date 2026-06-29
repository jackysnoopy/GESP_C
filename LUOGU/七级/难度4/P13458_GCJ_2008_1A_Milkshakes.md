# [GCJ 2008 #1A] Milkshakes

## 题目描述

You own a milkshake shop. There are $N$ different flavors that you can prepare, and each flavor can be prepared "malted" or "unmalted". So, you can make $2N$ different types of milkshakes.

Each of your customers has a set of milkshake types that they like, and they will be satisfied if you have at least one of those types prepared. At most one of the types a customer likes will be a "malted" flavor.

You want to make $N$ batches of milkshakes, so that:

- There is exactly one batch for each flavor of milkshake, and it is either malted or unmalted.
- For each customer, you make at least one milkshake type that they like.
- The minimum possible number of batches are malted.

Find whether it is possible to satisfy all your customers given these constraints, and if it is, what milkshake types you should make.

If it is possible to satisfy all your customers, there will be only one answer which minimizes the number of malted batches.

## 输入格式

One line containing an integer $C$, the number of test cases in the input file.

For each test case, there will be:

* One line containing the integer $N$, the number of milkshake flavors.
* One line containing the integer $M$, the number of customers.
* $M$ lines, one for each customer, each containing:
    * An integer $T \geq 1$, the number of milkshake types the customer likes, followed by
    * $T$ pairs of integers "X Y", one for each type the customer likes, where $X$ is the milkshake flavor between $1$ and $N$ inclusive, and $Y$ is either $0$ to indicate unmalted, or $1$ to indicated malted.

Note that:

* No pair will occur more than once for a single customer.
* Each customer will have at least one flavor that they like ($T \geq 1$).
* Each customer will like at most one malted flavor. (At most one pair for each customer has $Y = 1$).

All of these numbers are separated by single spaces.

## 输出格式

$C$ lines, one for each test case in the order they occur in the input file, each containing the string "Case #$X$: " where $X$ is the number of the test case, starting from $1$, followed by:

* The string "IMPOSSIBLE", if the customers' preferences cannot be satisfied; OR
* $N$ space-separated integers, one for each flavor from $1$ to $N$, which are $0$ if the corresponding flavor should be prepared unmalted, and $1$ if it should be malted.

## 样例

### 样例输入 1
```
2
5
3
1 1 1
2 1 0 2 0
1 5 0
1
2
1 1 0
1 1 1
```

### 样例输出 1
```
Case #1: 1 0 0 0 0
Case #2: IMPOSSIBLE
```

## 提示

**Sample Explanation**

In the first case, you must make flavor #1 malted, to satisfy the first customer. Every other flavor can be unmalted. The second customer is satisfied by getting flavor #2 unmalted, and the third customer is satisfied by getting flavor #5 unmalted.

In the second case, there is only one flavor. One of your customers wants it malted and one wants it unmalted. You cannot satisfy them both.

**Limits**

**Small dataset (10 Pts, Test set 1 - Visible)**

- $C = 100$
- $1 \leq N \leq 10$
- $1 \leq M \leq 100$

**Large dataset (25 Pts, Test set 2 - Hidden)**

- $C = 5$
- $1 \leq N \leq 2000$
- $1 \leq M \leq 2000$

The sum of all the $T$ values for the customers in a test case will not exceed $3000$.

## 解题思路

### 问题分析

$N$ 种口味的奶昔，每种可选 malted 或 unmalted。$M$ 个顾客各喜欢若干种，至少满足一种。目标是最小化 malted 数量。

### 核心思路

贪心算法：初始所有口味设为 unmalted。对每个顾客，若其喜欢的口味中已有满足的则跳过；否则必须将该顾客喜欢的唯一 malted 口味设为 malted（若无 malted 选项则无解）。

### 算法流程

1. 初始化所有口味为 unmalted
2. 对每个顾客：
   - 检查其喜欢的口味中是否已有满足的
   - 若无满足且有 malted 选项，将其设为 malted
   - 若无满足且无 malted 选项，输出 IMPOSSIBLE
3. 输出最终方案

### 复杂度分析

- 时间复杂度：$O(M \times T)$，$T$ 为每顾客喜欢的口味数
- 空间复杂度：$O(N + M)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int C;
    cin >> C;

    for (int c = 1; c <= C; c++) {
        int N, M;
        cin >> N >> M;

        vector<vector<pair<int, int>>> customers(M);
        for (int i = 0; i < M; i++) {
            int T;
            cin >> T;
            for (int j = 0; j < T; j++) {
                int x, y;
                cin >> x >> y;
                customers[i].push_back({x, y});
            }
        }

        vector<int> result(N, 0);
        bool possible = true;

        for (int i = 0; i < M; i++) {
            bool satisfied = false;
            int malted = -1;
            for (auto& [flavor, type] : customers[i]) {
                if (result[flavor - 1] == type) {
                    satisfied = true;
                    break;
                }
                if (type == 1) malted = flavor - 1;
            }
            if (!satisfied) {
                if (malted == -1) {
                    possible = false;
                    break;
                }
                result[malted] = 1;
            }
        }

        cout << "Case #" << c << ": ";
        if (!possible) {
            cout << "IMPOSSIBLE\n";
        } else {
            for (int i = 0; i < N; i++) {
                if (i) cout << " ";
                cout << result[i];
            }
            cout << "\n";
        }
    }

    return 0;
}
```
