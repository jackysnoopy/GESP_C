# [GKS 2019 #G] The Equation

## 题目描述

The laws of the universe can be represented by an array of $N$ non-negative integers. The i-th of these integers is $A_i$.

The universe is *good* if there is a non-negative integer $k$ such that the following equation is satisfied: $(A_1 \text{ xor } k) + (A_2 \text{ xor } k) + ... (A_N \text{ xor } k) \le M$, where xor denotes the bitwise exclusive or.

What is the largest value of $k$ for which the universe is good?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing the two integers $N$ and $M$, the number of integers in $A$ and the limit on the equation, respectively.

The second line contains $N$ integers, the i-th of which is $A_i$, the i-th integer in the array.

## 输出格式

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the largest value of k for which the universe is good, or $-1$ if there is no such $k$.

## 样例

### 样例输入 1
```
4
3 27
8 2 4
4 45
30 0 4 11
1 0
100
6 2
5 5 1 5 1 0
```

### 样例输出 1
```
Case #1: 12
Case #2: 14
Case #3: 100
Case #4: -1
```

## 提示

In sample case #1, the array contains $N = 3$ integers and $M = 27$. The largest possible value of $k$ that gives a good universe is $12$ ($(8 \text{ xor } 12) + (2 \text{ xor } 12) + (4 \text{ xor } 12) = 26$).

In sample case #2, the array contains $N = 4$ integers and $M = 45$. The largest possible value of $k$ that gives a good universe is $14$ ($(30 \text{ xor } 14) + (0 \text{ xor } 14) + (4 \text{ xor } 14) + (11 \text{ xor } 14) = 45$).

In sample case #3, the array contains $N = 1$ integer and $M = 0$. The largest possible value of $k$ that gives a good universe is $100$ ($100 \text{ xor } 100 = 0$).

In sample case #4, there is no value of $k$ that gives a good universe, so the answer is $-1$.

### Limits

$1 \le T \le 100$.

$1 \le N \le 1000$.

**Test set 1 (Visible)**

$0 \le M \le 100$.

$0 \le A_i \le 100$, for all $i$.

**Test set 2 (Hidden)**

$0 \le M \le 10^{15}$.

$0 \le A_i \le 10^{15}$, for all $i$.

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
        long long M;
        cin >> N >> M;

        vector<long long> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];

        long long ans = -1;

        for (long long k = 0; k <= 1000000; k++) {
            long long sum = 0;
            for (int i = 0; i < N; i++) {
                sum += (A[i] ^ k);
            }
            if (sum <= M) {
                ans = k;
            } else {
                break;
            }
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
```
