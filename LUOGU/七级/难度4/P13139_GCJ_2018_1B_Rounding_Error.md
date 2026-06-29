# [GCJ 2018 #1B] Rounding Error

## 题目描述

To finally settle the age-old question of which programming language is the best, you are asking a total of $\mathbf{N}$ people to tell you their favorite language. This is an open-ended question: each person is free to name any language, and there are infinitely many languages in the world.

Some people have already responded, and you have gathered this information as a list of counts. For example, 1 2 means that you have asked 3 people so far, and one picked a particular language, and the other two picked some other language.

You plan to publish the results in a table listing each language and the percentage of people who picked it. You will round each percentage to the nearest integer, rounding up any percentage with a decimal part equal to or greater than 0.5. So, for example, $12.5 \%$ would round up to $13 \%, 99.5 \%$ would round up to $100 \%$, and $12.4999 \%$ would round down to $12 \%$.

In surveys like this, sometimes the rounded percentages do not add up to exactly 100. After you are done surveying the remaining people, what is the largest value that the rounded percentages could possibly add up to?

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow; each consists of two lines. The first line consists of two integers $\mathbf{N}$ and $\mathbf{L}$ : the total number of people in the survey, and the total number of different languages represented among the people who have already responded. The second line consists of $\mathbf{L}$ integers $\mathbf{C}_{\mathbf{i}}$; the $i$-th of these is the number of people who said that the $i$-th of the represented languages was their favorite.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the largest value that the percentages could possibly add up to, as described above.

## 样例

### 样例输入 1
```
4
3 2
1 1
10 3
1 3 2
6 2
3 1
9 8
1 1 1 1 1 1 1 1
```

### 样例输出 1
```
Case #1: 100
Case #2: 100
Case #3: 101
Case #4: 99
```

## 提示

**Sample Explanation**

In Sample Case #1, two people have already responded, and they have chosen different languages. One person has not yet responded. If that person chooses a third language, then the rounded percentages will add up to $33+33+33=99$. However, if that person chooses one of the already-chosen languages, then the rounded percentages will add up to $67+33=100$. So 100 is the maximum possible sum.

In Sample Case #2, regardless of what the other four people choose, the percentages for the various languages will always be exact multiples of 10 that do not need to be rounded, and they will add up to exactly 100 .

In Sample Case #3, one optimal scenario is as follows: each of the remaining two people chooses an unchosen language, so the rounded percentages add up to $50+17+17+17=101$.

In Sample Case #4, whether or not the remaining person chooses an already-chosen language, the rounded percentages will add up to $99$.

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- $1 \leqslant \mathbf{L}<\mathbf{N}$.
- $1 \leqslant \mathbf{C}_{\mathbf{i}}$, for all $i$.
- The sum of all $\mathbf{C}_{\mathbf{i}}$ values $<\mathbf{N}$.

**Test set 1 (5 Pts, Visible)**

- $2 \leqslant \mathbf{N} \leqslant 25$.

**Test set 2 (9 Pts, Visible)**

- $2 \leqslant \mathbf{N} \leqslant 250$.

**Test set 3 (11 Pts, Hidden)**

- $2 \leqslant \mathbf{N} \leqslant 10^{5}$.

## 解题思路

### 问题分析
给定N个人和L种语言的投票数，剩余的人可以任意选择语言。每个语言的百分比四舍五入到整数，求所有语言四舍五入后百分比之和的最大值。

### 核心思路
利用贪心策略最大化四舍五入后的总和。关键观察：
- 四舍五入的本质：百分比的小数部分≥0.5时向上取整，否则向下取整
- 每增加一个人选择某种语言，该语言的百分比会增加$100/N$%
- 需要计算每个语言"四舍五入到整数"所需的最小增量

### 算法流程
1. 读入N、L和各语言投票数C[i]
2. 计算剩余人数remaining = N - sum(C)
3. 对于每个已投票语言：
   - 计算当前百分比pct = 100 * C[i] / N
   - 累加当前四舍五入值到base
   - 计算该语言的"分数距离"frac[i]：
     - 如果小数部分≥0.5：frac = ceil(pct) - pct（已经向上取整的距离）
     - 否则：frac = 0.5 - rem（距离四舍五入还需要的增量）
4. 将frac数组排序（贪心选择代价最小的语言）
5. 遍历剩余人数，对于每个剩余的人：
   - 如果frac[i] ≈ 0（已向上取整），直接extra++
   - 否则如果frac[i] ≤ 1/N（一个人的增量就能让它四舍五入），extra++
6. 输出base + extra

### 复杂度分析
- 时间复杂度：$O(L \log L)$，主要来自排序操作
- 空间复杂度：$O(L)$，存储各语言的分数距离

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N, L;
        cin >> N >> L;

        vector<int> C(L);
        int sum = 0;
        for (int i = 0; i < L; i++) {
            cin >> C[i];
            sum += C[i];
        }

        int remaining = N - sum;
        int base = 0;
        vector<double> frac;

        for (int i = 0; i < L; i++) {
            double pct = 100.0 * C[i] / N;
            base += (int)floor(pct + 0.5);
            double rem = pct - floor(pct);
            if (rem >= 0.5 - 1e-9) {
                frac.push_back(ceil(pct) - pct);
            } else {
                frac.push_back(0.5 - rem);
            }
        }

        sort(frac.begin(), frac.end());

        int ans = base;
        int extra = 0;
        for (int i = 0; i < remaining; i++) {
            if (i < (int)frac.size() && frac[i] <= 1e-9) {
                extra++;
            } else if (i < (int)frac.size()) {
                double need = frac[i];
                if (need <= 1.0 / N + 1e-9) {
                    extra++;
                }
            }
        }

        cout << "Case #" << t << ": " << ans + extra << "\n";
    }

    return 0;
}
```
