# [GCJ 2021 #3] Build-A-Pair

## 题目描述

You want to build a pair of positive integers. To do that, you are given a list of decimal digits to use. You must use every digit in the list exactly once, but you get to choose which ones to use for the first integer and which ones to use for the second integer. You also get to choose the order of the digits within each integer, except you cannot put a zero as the most significant (leftmost) digit in either integer. Note that you cannot choose just a zero for one integer either, because it would not be positive.

For example, you could be given the list $[1, 0, 2, 0, 4, 3]$. Two of the valid pairs you can build are $(200, 143)$ and $(3, 12400)$. The following pairs, on the other hand, are not valid:

* $(0102, 34)$: has a leading zero.
* $(0, 12340)$: has a non-positive integer.
* $(10, 243)$ and $(12300, 47)$: the list of digits in each of these pairs is not exactly equal to the given list of digits.

Given the list of digits to use, what is the minimum absolute difference between the two built integers that can be achieved?

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ lines follow. Each line describes a test case with a single string of digits $\mathbf{D}$. Each character of $\mathbf{D}$ is a digit you must use.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the minimum possible absolute difference between the two integers built from $\mathbf{D}$ according to the rules above.

## 样例

### 样例输入 1
```
4
1234
0011
07080
0899
```

### 样例输出 1
```
Case #1: 7
Case #2: 0
Case #3: 620
Case #4: 1
```

## 提示

**Sample Explanation**

The optimal pair of integers to build are $31$ and $24$ for Sample Case #1, $10$ and $10$ for Sample Case #2, $700$ and $80$ for Sample Case #3, and $89$ and $90$ for Sample Case #4.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- Each character of $\mathbf{D}$ is a decimal digit.
- At least two characters of $\mathbf{D}$ are not $\emptyset$.

**Test Set 1 (3 Pts, Visible Verdict)**

- $2 \leq$ the length of $\mathbf{D} \leq 8$.

**Test Set 2 (12 Pts, Visible Verdict)**

- $2 \leq$ the length of $\mathbf{D} \leq 36$.

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
        string D;
        cin >> D;

        sort(D.begin(), D.end());

        long long ans = 1e18;

        do {
            int n = D.size();
            for (int mask = 1; mask < (1 << n); mask++) {
                if (__builtin_popcount(mask) == 0 || __builtin_popcount(mask) == n) continue;

                string s1, s2;
                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) s1 += D[i];
                    else s2 += D[i];
                }

                if (s1[0] == '0' || s2[0] == '0') continue;

                long long v1 = stoll(s1);
                long long v2 = stoll(s2);
                ans = min(ans, abs(v1 - v2));
            }
        } while (next_permutation(D.begin(), D.end()));

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
```
