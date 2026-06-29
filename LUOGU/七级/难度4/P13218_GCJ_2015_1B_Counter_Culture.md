# [GCJ 2015 #1B] Counter Culture

## 题目描述

In the Counting Poetry Slam, a performer takes the microphone, chooses a number $N$, and counts aloud from $1$ to $N$. That is, she starts by saying $1$, and then repeatedly says the number that is $1$ greater than the previous number she said, stopping after she has said $N$.

It's your turn to perform, but you find this process tedious, and you want to add a twist to speed it up: sometimes, instead of adding $1$ to the previous number, you might reverse the digits of the number (removing any leading zeroes that this creates). For example, after saying "16", you could next say either "17" or "61"; after saying "2300", you could next say either "2301" or "32". You may reverse as many times as you want (or not at all) within a performance.

The first number you say must be $1$; what is the fewest number of numbers you will need to say in order to reach the number $N$? $1$ and $N$ count toward this total. If you say the same number multiple times, each of those times counts separately.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow. Each has one integer $N$, the number you must reach.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the test case number (starting from $1$) and $y$ is the minimum number of numbers you need to say.

## 样例

### 样例输入 1
```
3
1
19
23
```

### 样例输出 1
```
Case #1: 1
Case #2: 19
Case #3: 15
```

## 提示

**Sample Explanation**

In Case #2, flipping does not help and the optimal strategy is to just count up to $19$.

In Case #3, the optimal strategy is to count up to $12$, flip to $21$, and then continue counting up to $23$. That is, the numbers you will say are $1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 21, 22, 23$.

**Limits**

- $1 \leq T \leq 100$.

**Small dataset**

- Time limit: ~~240~~ 5 seconds.
- $1 \leq N \leq 10^6$.

**Large dataset**

- Time limit: ~~480~~ 10 seconds.
- $1 \leq N \leq 10^{14}$.

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
        long long N;
        cin >> N;

        long long ans = 0;
        long long cur = 1;

        while (cur < N) {
            string s = to_string(cur);
            string rev = s;
            reverse(rev.begin(), rev.end());
            long long r = stoll(rev);

            if (r > cur && r <= N) {
                cur = r;
                ans++;
            } else {
                cur++;
                ans++;
            }
        }

        cout << "Case #" << t << ": " << ans + 1 << "\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析
从数字 1 开始计数到 N，每次可以选择 +1 或反转数字（去掉前导零），求最少需要说出多少个数字。

### 核心思路
贪心策略：每一步优先选择反转操作（如果反转后得到的数字更大且不超过 N），否则执行 +1 操作。

### 算法流程
1. 初始化 cur = 1，ans = 0
2. 当 cur < N 时循环：
   - 将 cur 转为字符串并反转得到 r
   - 若 r > cur 且 r ≤ N，则执行反转操作：cur = r，ans++
   - 否则执行 +1 操作：cur++，ans++
3. 输出 ans + 1（包含起始数字 1）

### 复杂度分析
- 时间复杂度：O(N)，最坏情况下需要逐步 +1
- 空间复杂度：O(log N)，用于字符串操作
