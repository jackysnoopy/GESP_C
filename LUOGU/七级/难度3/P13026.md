# [GCJ 2021 #1A] Append Sort

## 题目描述

给定整数列表 $X_1, X_2, \ldots, X_N$，不能重排，只能通过在每个数右侧追加若干位十进制数字（$0$–$9$）来改变它。例如 $10$ 一次操作可变成 $100$ 或 $109$，两次操作可变成 $1034$。

求使列表严格递增所需的最少追加位操作总数。

## 输入格式

第一行 $T$。每组数据两行：第一行 $N$，第二行 $N$ 个整数 $X_i$。

## 输出格式

对每组数据输出 `Case #x: y`，$y$ 为最少追加操作数。

## 提示

**样例说明**：Case 1 `100 7 10` 需 4 次操作；Case 4 `1 2 3` 已严格递增，需 0 次。

**数据范围**：$1 \le T \le 100$，$2 \le N \le 100$，$1 \le X_i \le 10^9$（Test Set 2）。

时间限制 10000ms，内存限制 1GB。

## 解题思路

### 问题分析

只能在每个数的末尾追加数字（原数是新数的前缀），不能修改已有位。要从左到右保证严格递增，且每个数改得越小越好（对后续越有利）。因此采用**从左到右贪心**：对每个 $i$，在保证 $X_i' > X_{i-1}'$ 的前提下，让 $X_i'$ 尽可能小（追加位数尽可能少）。

### 核心思路

按字符串比较更方便（注意数值大小 = 先比位数再比字典序）。设 `bigger(a,b)` 表示数值 $a>b$：位数不同比位数，相同比字典序。

对 $i=1..N-1$，若 $X_i > X_{i-1}$ 已成立则无需操作；否则需追加数字让 $X_i' > X_{i-1}$，分情况（$l_a=|X_i|$，$l_b=|X_{i-1}|$）：

- **$l_a = l_b$**：追加 1 个 `0` 即可（位数变多必然更大），代价 1。
- **$l_a < l_b$**（$X_i$ 更短，$\text{diff}=l_b-l_a$）：比较 $X_i$ 与 $X_{i-1}$ 的前 $l_a$ 位 `prefix`：
  - $X_i = \text{prefix}$：补到等长会恰好等于 $X_{i-1}$，不够严格大。看 $X_{i-1}$ 剩余部分 `rest`：全为 9 则无法进位，需多补一位 → 追加 `diff+1` 个 `0`，代价 `diff+1`；否则把 `rest` 视为数 +1 后追加 → 代价 `diff`。
  - $X_i > \text{prefix}$：补 `diff` 个 `0` 凑到等长即更大，代价 `diff`。
  - $X_i < \text{prefix}$：补到等长仍更小，需多一位 → 追加 `diff+1` 个 `0`，代价 `diff+1`。

把更新后的 $X_i'$ 作为新的 $X_{i-1}$ 继续向右。每步取最小可行扩展，全局最优。

### 算法流程

1. 读入为字符串数组。
2. 对 $i=1..N-1$，按上述分情况追加数字并累加代价。
3. 输出总代价。

### 复杂度分析

- 时间复杂度：$O(N \cdot L)$，$L$ 为位数（操作后位数不超过 $10^9$ 的位数 + $N$），$N\le100$。
- 空间复杂度：$O(N\cdot L)$。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;
bool bigger(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() > b.size();
    return a > b;
}
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int n;
        cin >> n;
        vector<string> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        long long ans = 0;
        for (int i = 1; i < n; i++) {
            if (bigger(a[i], a[i-1])) continue;
            int la = a[i].size(), lb = a[i-1].size();
            if (la == lb) {
                a[i] += '0'; ans++;
            } else {
                int diff = lb - la;
                string prefix = a[i-1].substr(0, la);
                if (a[i] == prefix) {
                    string rest = a[i-1].substr(la);
                    bool all9 = true;
                    for (char c : rest) if (c != '9') { all9 = false; break; }
                    if (all9) {
                        a[i] += string(diff + 1, '0');
                        ans += diff + 1;
                    } else {
                        string nr = rest;
                        for (int k = nr.size() - 1; k >= 0; k--) {
                            if (nr[k] < '9') { nr[k]++; break; }
                            nr[k] = '0';
                        }
                        a[i] += nr;
                        ans += diff;
                    }
                } else if (a[i] > prefix) {
                    a[i] += string(diff, '0');
                    ans += diff;
                } else {
                    a[i] += string(diff + 1, '0');
                    ans += diff + 1;
                }
            }
        }
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
```
