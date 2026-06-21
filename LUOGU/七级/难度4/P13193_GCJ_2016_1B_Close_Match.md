# [GCJ 2016 #1B] Close Match

## 题目描述

You are attending the most important game in sports history. The Oceania Coders are playing the Eurasia Jammers in the Centrifugal Bumble-Puppy world finals. Unfortunately, you were sleep deprived from all the anticipation, so you fell asleep during the game!

The scoreboard is currently displaying both scores, perhaps with one or more leading zeroes (because the scoreboard displays a fixed number of digits). While you were asleep, some of the lights on the scoreboard were damaged by strong ball hits, so one or more of the digits in one or both scores are not being displayed.

You think close games are more exciting, and you would like to imagine that the scores are as close as possible. Can you fill in all of the missing digits in a way that minimizes the absolute difference between the scores? If there is more than one way to attain the minimum absolute difference, choose the way that minimizes the Coders' score. If there is more than one way to attain the minimum absolute difference while also minimizing the Coders' score, choose the way that minimizes the Jammers' score.

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ cases follow. Each case consists of one line with two non-empty strings $\mathbf{C}$ and $\mathbf{J}$ of the same length, composed only of decimal digits and question marks, representing the score as you see it for the Coders and the Jammers, respectively. There will be at least one question mark in each test case.

## 输出格式

For each test case, output one line containing `Case #x: c j`, where $x$ is the test case number (starting from 1), $c$ is $\mathbf{C}$ with the question marks replaced by digits, and $j$ is $\mathbf{J}$ with the question marks replaced by digits, such that the absolute difference between the integers represented by $c$ and $j$ is minimized. If there are multiple solutions with the same absolute difference, use the one in which $c$ is minimized; if there are multiple solutions with the same absolute difference and the same value of $c$, use the one in which $j$ is minimized.

## 样例

### 样例输入 1
```
4
1? 2?
?2? ??3
? ?
?5 ?0
```

### 样例输出 1
```
Case #1: 19 20
Case #2: 023 023
Case #3: 0 0
Case #4: 05 00
```

## 提示

**Sample Explanation**

In sample case #4, note that the answer cannot be 15 10; that minimizes the absolute difference, but does not minimize the Coders' score. Nor can the answer be 05 10; that minimizes the absolute difference and the Coders' score, but does not minimize the Jammers' score.

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 200$.
- $\mathbf{C}$ and $\mathbf{J}$ have the same length.

**Small dataset (Test Set 1 - Visible)**

- $1 \leqslant \text{the length of } \mathbf{C} \text{ and } \mathbf{J} \leqslant 3$.

**Large dataset (Test Set 2 - Hidden)**

- $1 \leqslant \text{the length of } \mathbf{C} \text{ and } \mathbf{J} \leqslant 18$.

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
        string C, J;
        cin >> C >> J;

        int n = C.size();
        long long best_diff = 1e18;
        string best_c = "", best_j = "";

        for (long long c_val = 0; c_val < (1LL << (n * 4)); c_val++) {
            string c_str = "";
            long long temp = c_val;
            for (int i = 0; i < n; i++) {
                c_str = char('0' + (temp % 10)) + c_str;
                temp /= 10;
            }

            bool valid_c = true;
            for (int i = 0; i < n; i++) {
                if (C[i] != '?' && C[i] != c_str[i]) {
                    valid_c = false;
                    break;
                }
            }
            if (!valid_c) continue;

            for (long long j_val = 0; j_val < (1LL << (n * 4)); j_val++) {
                string j_str = "";
                long long temp2 = j_val;
                for (int i = 0; i < n; i++) {
                    j_str = char('0' + (temp2 % 10)) + j_str;
                    temp2 /= 10;
                }

                bool valid_j = true;
                for (int i = 0; i < n; i++) {
                    if (J[i] != '?' && J[i] != j_str[i]) {
                        valid_j = false;
                        break;
                    }
                }
                if (!valid_j) continue;

                long long c_num = stoll(c_str);
                long long j_num = stoll(j_str);
                long long diff = abs(c_num - j_num);

                if (diff < best_diff || (diff == best_diff && c_num < stoll(best_c)) || (diff == best_diff && c_num == stoll(best_c) && j_num < stoll(best_j))) {
                    best_diff = diff;
                    best_c = c_str;
                    best_j = j_str;
                }
            }
        }

        cout << "Case #" << t << ": " << best_c << " " << best_j << "\n";
    }

    return 0;
}
```
