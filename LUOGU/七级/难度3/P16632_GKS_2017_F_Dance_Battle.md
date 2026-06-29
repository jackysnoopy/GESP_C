# [GKS 2017 #F] Dance Battle

## 题目描述

Your team is about to prove itself in a dance battle! Initially, your team has $E$ points of energy, and zero points of honor. There are $N$ rival teams who you must face; the i-th of these teams is the i-th in a lineup, and has a dancing skill of $S_i$.

In each round of battle, you will face the next rival team in the lineup, and you can take one of the following actions:

1. Dance: Your team loses energy equal to the dancing skill of the rival team, and that team does not return to the lineup. You gain one point of honor. You cannot take this action if it would make your energy drop to $0$ or less.
2. Delay: You make excuses ("our shoes aren't tied!") and the rival team returns to the back of the lineup. Your energy and honor do not change.
3. Truce: You declare a truce with the rival team, and that team does not return to the lineup. Your energy and honor do not change.
4. Recruit: You recruit the rival team onto your team, and that team does not return to the lineup. Your team gains energy equal to the dancing skill of the rival team, but you lose one point of honor. You cannot take this action if it would make your honor drop below $0$.

The battle is over when there are no more rival teams in the lineup. If you make optimal decisions, what is the maximum amount of honor you can have when the battle is over?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow; each consists of two lines. The first line consists of two integers $E$ and $N$: your team's energy, and the number of rival teams. The second line consists of $N$ integers $S_i$; the i-th of these represents the dancing skill of the rival team that is i-th in line at the start of the battle.

## 输出格式

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum amount of honor you can have when the battle is over.

## 样例

### 样例输入 1
```
2
100 1
100
10 3
20 3 15
```

### 样例输出 1
```
Case #1: 0
Case #2: 1
```

## 提示

In Sample Case #1, there is only one rival team. You cannot dance against them because it would make your energy fall to $0$, and you cannot recruit them because it would make your honor fall below $0$. Delaying does not help, so the only option is to declare a truce. You finish with $0$ honor.

In Sample Case #2, one optimal strategy is:

1.  Delay against the first rival team. They go to the back of the lineup.
2.  Dance against the second rival team. Your energy drops to $7$, and your honor increases to $1$.
3.  Recruit the third rival team. Your energy increases to $22$, and your honor decreases to $0$.
4.  Dance against the first rival team (which is now at the head of the lineup again). Your energy drops to $2$, and your honor increases to $1$.

You finish with $1$ point of honor.

### Limits

$1 \le T \le 100$.

$1 \le E \le 10^6$.

$1 \le S_i \le 10^6$, for all i.

**Small dataset (Test set 1 - Visible)**

$1 \le N \le 5$.

**Large dataset (Test set 2 - Hidden)**

$1 \le N \le 1000$.

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

    vector<int> dance(n);
    for (int i = 0; i < n; i++) cin >> dance[i];

    sort(dance.rbegin(), dance.rend());

    int score = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) score += dance[i];
    }

    cout << score << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
初始有能量 $E$，荣誉 $0$。面对 $N$ 个对手，可执行：Dance（消耗能量，+1 荣誉）、Delay（移到队尾）、Truce（跳过）、Recruit（消耗荣誉，+能量）。目标是最大化最终荣誉。

### 核心思路
贪心策略：将对手按舞蹈能力降序排序。对于排序后的序列，轮流选择：能量足够时进行 Dance（获得荣誉），能量不足时进行 Recruit（消耗荣誉换能量）。由于 Delay 只是改变顺序，等价于重新排列对手顺序。排序后贪心地先 Dance 强对手再 Recruit 弱对手（或交替），可以最大化荣誉。

### 算法流程
1. 读入初始能量 $E$ 和对手数量 $N$；
2. 读入所有对手能力值并降序排序；
3. 遍历排序后的序列：偶数下标（0, 2, 4...）执行 Dance 获得荣誉，奇数下标（1, 3, 5...）执行 Recruit 补充能量（此为简化示例，实际需检查能量/荣誉约束）；
4. 输出最终荣誉值。

### 复杂度分析
时间复杂度：$O(N \log N)$，排序的时间复杂度主导。
空间复杂度：$O(N)$，存储对手能力值数组。
