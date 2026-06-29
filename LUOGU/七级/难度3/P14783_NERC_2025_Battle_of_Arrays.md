# [NERC 2025] Battle of Arrays

## 题目描述

Alice and Bob play a turn-based game. Initially, Alice has an array $a$ of $n$ positive integers, and Bob has an array $b$ of $m$ positive integers. The players take turns, with Alice moving first.

On a player’s turn, they must choose one element $x$ from their own array and **the maximal** element $y$ from their opponent’s array. Then they perform the following operation:

- If $y \le x$: the element $y$ is destroyed (removed from the opponent’s array).
- If $y > x$: the element $y$ is decreased by $x$ (the value of $y$ becomes $y - x$).

A player wins if, after their move, the opponent’s array becomes empty.

Assuming both players play optimally, determine the winner.

## 输入格式

Each input contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^5$). The first line of each test case contains two integers $n$ and $m$ ($1 \le n, m \le 10^5$) — the sizes of Alice’s and Bob’s arrays respectively.

The second line contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le 10^9$) — Alice’s array.

The third line contains $m$ integers $b_1, b_2, \dots, b_m$ ($1 \le b_i \le 10^9$) — Bob’s array.

It is guaranteed that the sum of $n$ over all test cases does not exceed $10^5$ and the sum of $m$ over all test cases does not exceed $10^5$.

## 输出格式

For each test case, print the name of the winner of the game if both players follow the optimal strategy: “Alice” or “Bob”.

## 样例

### 样例输入 1
```
2
1 1
70
90
2 3
30 30
20 20 40
```

### 样例输出 1
```
Alice
Bob
```

## 提示

In the first test Alice moves and decreases Bob’s element by $70$, so it becomes $20$. Then Bob moves and decreases Alice’s element by $20$, so it becomes $50$. Finally, Alice moves, destroys Bob’s element, and wins.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > b[i]) ans++;
    }

    cout << ans << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
Alice 和 Bob 轮流操作，每次从自己数组选一个元素 $x$，对对手数组的最大元素 $y$ 执行操作：若 $y \le x$ 则删除 $y$，否则 $y$ 减去 $x$。Alice 先手，无法操作者输（对手数组空则该回合玩家获胜）。

约束：$n, m \le 10^5$，元素值 $\le 10^9$，总测试用例的 $n, m$ 之和 $\le 10^5$。

### 核心思路
这是一个博弈论问题。关键观察：每次操作必须针对对手的**最大**元素，因此操作顺序是确定性的。

分析每次操作的效果：用 $x$ 攻击 $y$，若 $y \le x$ 则直接消灭；否则 $y$ 变为 $y - x$。这类似于辗转相除的过程。

考虑将双方数组排序后，从小到大配对比较。核心结论：**将双方数组分别排序后，逐位比较 $a[i]$ 和 $b[i]$，$a[i] > b[i]$ 的个数决定 Alice 能比 Bob 多消灭多少个元素**。

具体地，排序后 Alice 的最大元素优先消灭 Bob 的最大元素，反之亦然。若 Alice 排序后的第 $i$ 大元素大于 Bob 排序后的第 $i$ 大元素，则 Alice 在该轮占优。

### 算法流程
1. 将 Alice 的数组 $a$ 和 Bob 的数组 $b$ 分别排序
2. 逐位比较：若 $a[i] > b[i]$，则 Alice 在该位置占优
3. 统计 Alice 占优的位置数，若大于 Bob 占优的位置数则 Alice 赢，否则 Bob 赢

### 复杂度分析
- 时间复杂度：$O(n \log n + m \log m)$（排序）
- 空间复杂度：$O(n + m)$
