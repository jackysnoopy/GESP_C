# [CCO 2023] Flip it and Stick it

## 题目描述

给定字符串 S 和 T（|T| ≤ 3）。每次操作可以翻转 S 的任意子串。求使 S 不包含 T 作为子串的最少操作次数，不可行输出 -1。

## 输入格式

第一行一个整数 q，表示询问次数。  
接下来 q 行，每行两个字符串 S 和 T。

## 输出格式

每次询问输出一个整数，表示最少操作次数或 -1。

## 样例

### 样例 1

**输入：**
```
3
abcde a
abcde b
aab aa
```

**输出：**
```
-1
-1
1
```

## 提示

- 1 ≤ |S| ≤ 2×10^5
- 1 ≤ |T| ≤ 3
- q 次询问的 |S| 之和 ≤ 2×10^5

## 解题思路

### 问题分析

翻转（反转）子串可以重排字符顺序。由于 |T| 很小（≤ 3），我们可以按 |T| 的长度分类讨论，利用字符计数和连续段分析来判断可行性并计算最少操作次数。

### 核心思路

**分类讨论（按 |T| 长度）**：

1. **|T| = 1**：T 是单个字符。翻转不改变字符集合，若 S 含 T 则无法消除，输出 -1。
2. **|T| = 2**：
   - T[0] = T[1]（如 "aa"）：需使无相邻相同字符。若某字符数量超过其余字符数+1 则不可行。否则通过分析连续段计算操作数。
   - T[0] ≠ T[1]（如 "ab"）：目标是将所有 T[1] 排到 T[0] 前面。操作数 = 连续段数 / 2 或 (连续段数-1) / 2。
3. **|T| = 3**：类似分类讨论，根据字符重复模式判断。

### 算法流程

1. 检查 S 是否已不含 T，若是则输出 0。
2. 按 |T| 分类：
   - |T| = 1：输出 -1。
   - |T| = 2：统计字符数和连续段数，判断可行性并计算操作数。
   - |T| = 3：根据 T 的字符模式（全同/两同/全异）分别处理。
3. 返回最少操作次数或 -1。

### 复杂度分析

- 时间：O(|S|) 每次询问。
- 空间：O(|S|)。

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int solve(string S, string T) {
    int n = S.size();
    int m = T.size();

    if (m == 1) {
        char c = T[0];
        for (int i = 0; i < n; i++) {
            if (S[i] == c) return -1;
        }
        return 0;
    }

    if (m == 2) {
        bool hasT = false;
        for (int i = 0; i + 1 < n; i++) {
            if (S[i] == T[0] && S[i + 1] == T[1]) {
                hasT = true;
                break;
            }
        }
        if (!hasT) return 0;

        if (T[0] == T[1]) {
            char c = T[0];
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == c) cnt++;
            }
            int other = n - cnt;
            if (cnt > other + 1) return -1;
            int runs = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == c && (i == 0 || S[i - 1] != c)) runs++;
            }
            if (runs <= 1) return 1;
            return 2;
        } else {
            int cntA = 0, cntB = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == T[0]) cntA++;
                if (S[i] == T[1]) cntB++;
            }
            if (cntA == 0 || cntB == 0) return 0;

            int runs = 1;
            for (int i = 1; i < n; i++) {
                if (S[i] != S[i - 1]) runs++;
            }
            if (S[0] == T[1]) {
                return (runs - 1) / 2;
            } else {
                return runs / 2;
            }
        }
    }

    if (m == 3) {
        bool hasT = false;
        for (int i = 0; i + 2 < n; i++) {
            if (S[i] == T[0] && S[i + 1] == T[1] && S[i + 2] == T[2]) {
                hasT = true;
                break;
            }
        }
        if (!hasT) return 0;

        if (T[0] == T[1] && T[1] == T[2]) {
            char c = T[0];
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == c) cnt++;
            }
            int other = n - cnt;
            if (cnt > other * 2 + 2) return -1;
            int runs = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == c && (i == 0 || S[i - 1] != c)) runs++;
            }
            return min(runs, 3);
        }

        if (T[0] == T[1] && T[1] != T[2]) {
            char c = T[0], d = T[2];
            int cntC = 0, cntD = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == c) cntC++;
                else if (S[i] == d) cntD++;
            }
            if (cntC == 0 || cntD == 0) return 0;
            int cntOther = n - cntC - cntD;
            if (cntC > cntD + cntOther + 1) return -1;
            return 1;
        }

        if (T[0] != T[1] && T[1] == T[2]) {
            char a = T[0], c = T[1];
            int cntA = 0, cntC = 0;
            for (int i = 0; i < n; i++) {
                if (S[i] == a) cntA++;
                else if (S[i] == c) cntC++;
            }
            if (cntA == 0 || cntC == 0) return 0;
            int cntOther = n - cntA - cntC;
            if (cntC > cntA + cntOther + 1) return -1;
            return 1;
        }

        if (T[0] != T[1] && T[0] != T[2] && T[1] != T[2]) {
            int cnt[3] = {0, 0, 0};
            for (int i = 0; i < n; i++) {
                if (S[i] == T[0]) cnt[0]++;
                else if (S[i] == T[1]) cnt[1]++;
                else if (S[i] == T[2]) cnt[2]++;
            }
            if (cnt[0] == 0 || cnt[1] == 0 || cnt[2] == 0) return 0;
            return 1;
        }

        int cnt[26] = {0};
        for (int i = 0; i < n; i++) cnt[S[i] - 'a']++;
        int runs = 1;
        for (int i = 1; i < n; i++) {
            if (S[i] != S[i - 1]) runs++;
        }
        return min(runs, 3);
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        string S, T;
        cin >> S >> T;
        cout << solve(S, T) << "\n";
    }
    return 0;
}
```
