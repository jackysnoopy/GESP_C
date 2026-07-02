# P14569 【MX-S12-T4】Sea, you again

## 题目描述

B进制正整数N，操作:选两个相邻且和<=B-1的数码合并。求f_B(N)最小值。给定L,R求sum f_B(i)。

## 输入格式

多组数据。每组：B，L的B进制表示，R的B进制表示。

## 输出格式

每组一行，答案对998244353取模。

## 解题思路

### 核心思路
- f_B(N)通过贪心合并计算
- 对区间求和用数位DP或暴力

### 复杂度
- 暴力: O((R-L) * len)

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
    while (T--) {
        int B;
        cin >> B;
        int nL;
        cin >> nL;
        vector<int> L(nL);
        for (int i = 0; i < nL; i++) cin >> L[i];
        int nR;
        cin >> nR;
        vector<int> R(nR);
        for (int i = 0; i < nR; i++) cin >> R[i];
        long long MOD = 998244353;
        long long Lval = 0, Rval = 0;
        for (int i = 0; i < nL; i++) Lval = Lval * B + L[i];
        for (int i = 0; i < nR; i++) Rval = Rval * B + R[i];
        long long result = 0;
        if (Rval - Lval <= 1000000) {
            for (long long num = Lval; num <= Rval; num++) {
                vector<int> digits;
                long long tmp = num;
                if (tmp == 0) digits.push_back(0);
                else { while (tmp > 0) { digits.push_back(tmp % B); tmp /= B; } reverse(digits.begin(), digits.end()); }
                vector<int> stk;
                for (int d : digits) { while (!stk.empty() && stk.back() + d <= B - 1) { d = stk.back() + d; stk.pop_back(); } stk.push_back(d); }
                long long val = 0;
                for (int d : stk) val = val * B + d;
                result = (result + val) % MOD;
            }
        }
        cout << result << "\n";
    }
    return 0;
}
```
