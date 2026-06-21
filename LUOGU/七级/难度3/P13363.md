# [GCJ 2011 Qualification] Candy Splitting

## 题目描述

Sean 和 Patrick 分一袋糖果。每颗糖果有价值 $C_i$。Sean 先把糖果分成两堆（均非空）并选一堆给 Patrick。Patrick 用他自己"不会进位"的二进制加法计算每堆价值：两数相加时逐位异或（忘记进位），即两堆价值均为各糖果价值的异或和。若他认为两堆价值不等就会哭。

Sean 想在保证 Patrick 不哭（两堆异或值相等）的前提下，使自己留下的那堆总价值最大。判断是否可能；若可能，输出 Sean 留下糖果堆的最大总价值。

## 输入格式

第一行测试组数 $T$（$1 \le T \le 100$）。每组两行：第一行整数 $N$（糖果数），第二行 $N$ 个整数 $C_i$（$1 \le C_i \le 10^6$）。

## 输出格式

对每组输出 `Case #x: y`。不可能则 `y` 为 `NO`；否则 `y` 为 Sean 留下糖果堆的最大总价值。

## 提示

- 小数据 $2 \le N \le 15$；大数据 $2 \le N \le 1000$。
- Patrick 的"加法"实质是按位异或（XOR），无进位。

## 解题思路

### 问题分析

- Patrick 把一堆的价值算成其中所有糖果价值的异或和。设两堆异或和为 $X_1, X_2$，要求 $X_1 = X_2$。
- 全体糖果异或和 $S = X_1 \oplus X_2$。若 $X_1 = X_2$，则 $S = 0$；反之若 $S=0$，任取一种划分都有 $X_1 = X_2$（因为 $X_2 = S \oplus X_1 = X_1$）。故"不哭"等价于全体异或和为 $0$。
- 当 $S=0$ 时，任意划分都满足两堆异或值相等。Sean 想最大化自己那堆的**普通总和**：把价值最小的一颗给 Patrick，其余全留给自己即可（给 Patrick 一颗 $c$ 时，Patrick 堆异或值 $=c$，Sean 堆异或值 $=S\oplus c = c$，相等，合法）。
- 两堆均非空：$N\ge 2$，给 Patrick 一颗、Sean 留 $N-1$ 颗即可。

### 核心思路

- 计算全体异或和 `xsum` 与总和 `total`、最小值 `mn`。
- 若 `xsum != 0` 输出 `NO`；否则输出 `total - mn`（Sean 留下除最小颗外的所有糖果）。

### 算法流程

1. 读入 $T$，对每组：
2. 读 $N$ 和各 $C_i$，同时累计异或和、总和、最小值。
3. 异或和为 $0$ 则答案为 `total - mn`，否则 `NO`。

### 复杂度分析

- 时间复杂度：$O(N)$ 每组，总计 $O(\sum N)$。
- 空间复杂度：$O(N)$（也可 $O(1)$ 流式处理）。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        vector<ll> c(N);
        ll xsum = 0, total = 0, mn = 1e18;
        for (int i = 0; i < N; i++) {
            cin >> c[i];
            xsum ^= c[i];
            total += c[i];
            mn = min(mn, c[i]);
        }
        cout << "Case #" << tc << ": ";
        if (xsum != 0) cout << "NO\n";
        else cout << total - mn << "\n";
    }
    return 0;
}
```
