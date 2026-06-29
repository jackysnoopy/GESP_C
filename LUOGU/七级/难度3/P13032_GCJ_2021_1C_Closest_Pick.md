# [GCJ 2021 #1C] Closest Pick

## 题目描述

You are entering a raffle for a lifetime supply of pancakes. $\textbf{N}$ tickets have already been sold. Each ticket contains a single integer between $1$ and $\textbf{K}$, inclusive. Different tickets are allowed to contain the same integer. You know exactly which numbers are on all of the tickets already sold and would like to maximize your odds of winning by purchasing two tickets (possibly with the same integer on them). You are allowed to choose which integers between $1$ and $\textbf{K}$, inclusive, are on the two tickets.

![](https://cdn.luogu.com.cn/upload/image_hosting/dzt1cd5t.png)

You know you are the last customer, so after you purchase your tickets, no more tickets will be purchased. Then, an integer $c$ between $1$ and $\textbf{K}$, inclusive, is chosen uniformly at random. If one of your tickets is strictly closer to $c$ than all other tickets or if both of your tickets are the same distance to $c$ and strictly closer than all other tickets, then you win the raffle. Otherwise, you do not win the raffle.

Given the integers on the $\textbf{N}$ tickets purchased so far, what is the maximum probability of winning the raffle you can achieve by choosing the integers on your two tickets optimally?

## 输入格式

The first line of the input gives the number of test cases, $\textbf{T}$. $\textbf{T}$ test cases follow. Each test case consists of two lines. The first line of a test case contains two integers $\textbf{N}$ and $\textbf{K}$: the number of tickets already sold and the limit of the range of integers to pick from, respectively. The second line contains $\textbf{N}$ integers $\textbf{P}_1, \textbf{P}_2, \ldots, \textbf{P}_\textbf{N}$, representing the integers on the tickets that have already been purchased.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from $1$) and $y$ is the maximum win probability you can achieve if you choose your tickets optimally. $y$ will be considered correct if it is within an absolute or relative error of $10^{-6}$ of the correct answer. See the FAQ for an explanation of what that means, and what formats of real numbers we accept.

## 样例

### 样例输入 1
```
4
3 10
1 3 7
4 10
4 1 7 3
4 3
1 2 3 2
4 4
1 2 4 2
```

### 样例输出 1
```
Case #1: 0.5
Case #2: 0.4
Case #3: 0.0
Case #4: 0.25
```

## 提示

**Sample Explanation**

In Sample Case #1, you can purchase tickets with the integers $4$ and $8$ on them and then win if $4$, $5$, $8$, $9$, or $10$ are chosen giving you $\frac{5}{10} = 0.5$ probability of winning. Purchasing tickets with the integers $6$ and $8$ on them also yields a $0.5$ probability of winning, but no combination yields more.

In Sample Case #2, $6$ and $8$ is a possible optimal pair of tickets, which wins when $c$ is one of $6$, $8$, $9$, or $10$. Note that the integers on the tickets are not necessarily given in sorted order.

In Sample Case #3, every possible $c$ is at distance $0$ from an already purchased ticket, so you cannot win regardless of your choices.

In Sample Case #4, if you pick $3$ for at least one of your tickets, you win on $c = 3$, for $\frac{1}{4} = 0.25$ win probability. There is no way to win when $c$ is any other integer, so that is the best you can do.

**Limits**

- $1 \leq \textbf{T} \leq 100$.
- $1 \leq \textbf{N} \leq 30$.
- $1 \leq \textbf{P}_i \leq \textbf{K}$, for all $i$.

**Test Set 1 (9 Pts, Visible Verdict)**

- $1 \leq \textbf{K} \leq 30$.

**Test Set 2 (16 Pts, Visible Verdict)**

- $1 \leq \textbf{K} \leq 10^9$.

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
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N, K;
        cin >> N >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        sort(P.begin(), P.end());
        P.erase(unique(P.begin(), P.end()), P.end());
        int m = P.size();
        vector<int> gaps;
        if (m == 0) {
            cout << "Case #" << tc << ": " << fixed << setprecision(9) << 1.0 << "\n";
            continue;
        }
        if (m == 1) {
            int cov = K - 1;
            cout << "Case #" << tc << ": " << fixed << setprecision(9) << (double)cov / K << "\n";
            continue;
        }
        gaps.push_back(P[0] - 1);
        gaps.push_back(K - P[m-1]);
        for (int i = 0; i + 1 < m; i++)
            gaps.push_back((P[i+1] - P[i]) / 2);
        sort(gaps.rbegin(), gaps.rend());
        int best = max(gaps[0], (m >= 2 ? (gaps[0] + (gaps.size() > 1 ? gaps[1] : 0)) : gaps[0]));
        // Also consider full gap (two tickets in same gap)
        int fullGap = P[0] - 1;
        fullGap = max(fullGap, K - P[m-1]);
        for (int i = 0; i + 1 < m; i++)
            fullGap = max(fullGap, P[i+1] - P[i] - 1);
        best = max(best, fullGap);
        // Also: two largest one-ticket coverages
        int sum2 = gaps[0];
        if (gaps.size() > 1) sum2 += gaps[1];
        best = max(best, sum2);
        cout << "Case #" << tc << ": " << fixed << setprecision(9) << (double)best / K << "\n";
    }
    return 0;
}
```