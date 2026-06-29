# [GCJ 2011 #3] Dire Straights

## 题目描述

You are playing a card game, where each card has an integer number written on it.

To play the game, you are given some cards — your $hand$. Then you arrange the cards in your hand into $straights$. A straight is a set of cards with consecutive values; e.g. the three cards $\{3, 4, 5\}$, or the single card $\{7\}$. You then receive a number of dollars equal to the length of the shortest straight. If you have no cards, you can form no straights, so you get zero dollars.

You will be given a series of test cases, each of which describes the cards you will have in your hand. Find the maximum number of dollars you can receive for each test case.

## 输入格式

The first line of the input contains the number of test cases, $T$. Each test case consists of one line. Each line contains $N$, the number of cards in your hand, followed by $N$ integers giving the numbers on those cards. These numbers are all space-separated.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the maximum number of dollars you can receive.

## 样例

### 样例输入 1
```
4
10 1 2 3 4 5 10 9 8 7 6
8 101 102 103 104 105 106 103 104
0
5 1 2 3 4 9
```

### 样例输出 1
```
Case #1: 10
Case #2: 4
Case #3: 0
Case #4: 1
```

## 提示

**Sample Explanation**

In case 1, you have ten cards numbered $1$ to $10$, so you make one straight of length $10$, and get $10$ dollars.

In case 2, you could make two straights $\{101, 102, 103, 104, 105, 106\}$ and $\{103, 104\}$ and get $2$ dollars. But it would be better to make $\{101, 102, 103, 104\}$ and $\{103, 104, 105, 106\}$ and get $4$ dollars.

In case 4, the card with the number $9$ must be in a straight containing only that card. So you get $1$ dollar.

In case 3, you have zero cards, so you get zero dollars. You don't get money for nothing.

**Limits**

- $1 \leq T \leq 100$
- The numbers on the cards are between $1$ and $10000$.

**Small dataset (4 Pts, Test set 1 - Visible)**

- $0 \leq N \leq 10$
- Time limit: ~~30~~ 3 seconds.

**Large dataset (12 Pts, Test set 2 - Hidden)**

- $0 \leq N \leq 1000$
- Time limit: ~~60~~ 6 seconds.

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

    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;

        vector<int> cards(N);
        for (int i = 0; i < N; i++) cin >> cards[i];

        sort(cards.begin(), cards.end());

        int ans = 0;
        int i = 0;

        while (i < N) {
            int j = i;
            while (j < N && cards[j] == cards[i] + (j - i)) j++;
            ans = max(ans, j - i);
            i = j;
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析
给定若干张牌，每张牌上有一个整数。需要将牌分成若干"顺子"（连续整数序列），收益为最短顺子的长度。目标是最大化这个最小值。

### 核心思路
将牌排序后，连续的、差值为1的牌自然构成一个顺子。由于收益取决于最短顺子，最优策略是让每个顺子尽可能长——排序后直接扫描找最长的连续递增子序列即可。

### 算法流程
1. 将所有牌的数字排序
2. 用双指针从左到右扫描排序后的数组
3. 对于每个起点 i，向右扩展 j，使得 cards[j] == cards[i] + (j - i)（即连续递增）
4. 记录每段连续子序列的长度 j - i，取最大值
5. 输出最大值即为答案

### 复杂度分析
- 时间复杂度：O(N log N)（排序）+ O(N)（扫描），总 O(N log N)
- 空间复杂度：O(N)（存储牌面数字）
