# P13139 - [GCJ 2018 #1B] Rounding Error

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

### Sample 1
**Input:**
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

**Output:**
```
Case #1: 100
Case #2: 100
Case #3: 101
Case #4: 99
```

## 样例解释

**Sample Explanation**

In Sample Case #1, two people have already responded, and they have chosen different languages. One person has not yet responded. If that person chooses a third language, then the rounded percentages will add up to $33+33+33=99$. However, if that person chooses one of the already-chosen languages, then the rounded percentages will add up to $67+33=100$. So 100 is the maximum possible sum.

In Sample Case #2, regardless of what the other four people choose, the percentages for the various languages will always be exact multiples of 10 that do not need to be rounded, and they will add up to exactly 100 .

In Sample Case #3, one optimal scenario is as follows: each of the remaining two people chooses an unchosen language, so the rounded percentages add up to $50+17+17+17=101$.

In Sample Case #4, whether or not the remaining person chooses an already-chosen language, the rounded percentages will add up to $99$.

## 数据范围

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

这道题是一个关于百分比四舍五入的问题。我们需要最大化四舍五入后的百分比之和。

关键观察：
1. 每个语言的百分比是 $C_i / N * 100$
2. 四舍五入后，百分比之和可能不等于 100
3. 我们可以通过分配剩余的人来最大化这种增加

### 算法设计

1. **计算当前百分比之和**：对于每个语言，计算其百分比并四舍五入
2. **贪心分配**：将剩余的人分配给能最大化四舍五入值增加的语言
3. **考虑创建新语言**：有时候创建新语言能获得更大的四舍五入值

### 关键点

- 优先分配给那些小数部分接近 0.5 的语言
- 考虑创建新语言的情况

## 算法原理

本题采用贪心算法。对于每个剩余的人，我们选择能最大化四舍五入值增加的语言（包括创建新语言）。

## 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
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
        
        // 计算每个语言的当前百分比和四舍五入后的值
        int totalRounded = 0;
        for (int i = 0; i < L; i++) {
            double percent = (double)C[i] * 100.0 / N;
            int rounded = (int)(percent + 0.5);
            totalRounded += rounded;
        }
        
        // 尝试将剩余的人分配给语言，使得四舍五入后的值增加
        vector<int> current = C;
        int maxTotal = totalRounded;
        
        for (int i = 0; i < remaining; i++) {
            // 找到能增加最多四舍五入值的语言
            int bestLang = -1;
            int bestGain = -1;
            
            // 检查已有的语言
            for (int j = 0; j < L; j++) {
                double newPercent = (double)(current[j] + 1) * 100.0 / N;
                int newRounded = (int)(newPercent + 0.5);
                double oldPercent = (double)current[j] * 100.0 / N;
                int oldRounded = (int)(oldPercent + 0.5);
                int gain = newRounded - oldRounded;
                
                if (gain > bestGain) {
                    bestGain = gain;
                    bestLang = j;
                }
            }
            
            // 检查创建新语言
            double newPercent = 100.0 / N;
            int newRounded = (int)(newPercent + 0.5);
            if (newRounded > bestGain) {
                bestGain = newRounded;
                bestLang = L;
            }
            
            if (bestLang == L) {
                current.push_back(1);
                L++;
                maxTotal += bestGain;
            } else if (bestGain > 0) {
                current[bestLang]++;
                maxTotal += bestGain;
            }
        }
        
        cout << "Case #" << t << ": " << maxTotal << endl;
    }
    
    return 0;
}
```

## 复杂度分析

- **时间复杂度**：O(T * N * L)，其中 N 是总人数，L 是语言数量
- **空间复杂度**：O(L)，用于存储语言计数

## 注意事项

1. 这个解法适用于所有测试集
2. 关键是正确计算四舍五入值和贪心分配
3. 考虑创建新语言的情况
