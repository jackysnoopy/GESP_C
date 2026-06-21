# [GCJ Farewell Round #1] Untie

## 题目描述

一群人围成一圈玩石头剪刀布。每人秘密选择 `R`（石头）、`P`（布）、`S`（剪刀）之一后同时亮出。每个人与左右两位邻居各比一次，可能赢、输或平；**只有双方选择相同时才平局**。

目标是让所有相邻对都不平局（即相邻两人选择不同）。对每个人，你可以让他保持原选择，或让他改成另外两个选项中的任意一个（由你决定改成哪个）。求最少需要让多少人改变选择。

## 输入格式

第一行一个整数 $T$，表示测试数据组数。接下来 $T$ 行，每行一个字符串 $C$，第 $i$ 个字符表示第 $i$ 个人（顺时针）的原始选择，为 `R`、`P`、`S` 之一。

## 输出格式

对每组数据输出一行 `Case #x: y`，其中 $x$ 为数据编号（从 1 起），$y$ 为使相邻两人都不相同所需的最少改变人数。

## 提示

**样例说明**：
- Case 1 `PRSSP`：有两组邻居相同（首尾的 `P`、中间的 `S`），至少改 2 人，例如改成 `SRSRP`。
- Case 2 `RRRRRRR`：7 人全是 `R`，改至多 3 人仍会剩至少 4 个 `R` 且必有相邻，故至少 4 人，例如 `PRSRPRS`。
- Case 3 `RSPRPSPRS`：本就无相邻相同，无需改变。

**数据范围**：$1 \le T \le 100$，$3 \le |C| \le 1000$（Test Set 2）。

时间限制 10000ms，内存限制 2GB。

## 解题思路

### 问题分析

等价于：给圆环上每个位置重新着色（可保持原色，或改成另外两色之一），使相邻颜色都不同（圆环的合法 3-染色），最小化改变的位置数。也即最大化"保持原色"的位置数。

### 核心思路

将字符串划分成**极大连续同色段（run）**。同一 run 内相邻位置颜色相同会平局，必须隔一个改一个；不同 run 之间相邻位置颜色本就不同，两端都可保持。因此各 run 在计数上相互独立，唯一要处理的是**圆环首尾**：若 $C_0 = C_{n-1}$，则首尾两个 run 在圆环上其实相连，应合并。

- 若全串只有 1 个 run（全同色，构成一个**环**）：保持的位置构成该环的最大独立集，大小 $\lfloor n/2\rfloor$，故改变数 $= n-\lfloor n/2\rfloor = \lceil n/2\rceil = (n+1)/2$。
- 否则每个 run 都是一条**链**（两端被不同色的相邻 run 夹住，端点可与不同色邻居同时保持）：长 $L$ 的链最大可保持 $\lceil L/2\rceil$ 个，改变 $\lfloor L/2\rfloor$ 个。
  - 若 $C_0 = C_{n-1}$：首尾 run 合并为一条长 $a+b$ 的链，贡献 $\lfloor(a+b)/2\rfloor$，其余中间 run 各贡献 $\lfloor L_i/2\rfloor$。
  - 若 $C_0 \ne C_{n-1}$：所有 run 各贡献 $\lfloor L_i/2\rfloor$。

**可实现性**：run 内原色为 $X$，被改变的位置只能取另两色 $Y,Z$；在保持的 $X$ 之间的空段用 $Y,Z$ 交替填充即可保证相邻不同，且改变后的颜色 $\ne X$ 满足"改成另外两色"的要求。run 边界两端颜色不同可同时保持。故上述计数即为答案（已通过暴力对拍验证）。

### 算法流程

1. 读入串 $s$，$n=|s|$。$n\le1$ 时答案为 0。
2. 压缩为 run 列表（字符 + 长度）。
3. 分三类计算：
   - run 数为 1：`ans = (n+1)/2`；
   - 否则若 $s[0]=s[n-1]$：`ans = (runs[0].len + runs.back().len) / 2`，再加上中间各 run 的 `len/2`；
   - 否则：`ans = Σ runs[i].len / 2`。
4. 输出 `Case #x: ans`。

### 复杂度分析

- 时间复杂度：$O(n)$ 每组数据。
- 空间复杂度：$O(n)$。

## ⚠️ 代码勘误

仓库中的 `P12950.cpp` 原始版本在 $s[0]=s[n-1]$ 的合并分支里使用了**上取整** `(mergedLen + 1) / 2`，正确应为**下取整** `mergedLen / 2`。这导致合并段长度为奇数时答案偏大，例如 `SPSS` 应输出 `1`，原代码输出 `2`（已用暴力验证：随机小数据中原代码错误率约 11%）。下方参考代码为修正版（仅改一行）。

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        string s;
        cin >> s;
        int n = s.size();
        if (n <= 1) { cout << "Case #" << tc << ": 0\n"; continue; }
        vector<pair<char,int>> runs;
        for (int i = 0; i < n; i++) {
            if (runs.empty() || runs.back().first != s[i])
                runs.push_back({s[i], 1});
            else
                runs.back().second++;
        }
        int ans = 0;
        if (runs.size() == 1) {
            ans = (n + 1) / 2;
        } else if (s[0] == s[n-1]) {
            int mergedLen = runs[0].second + runs.back().second;
            ans = mergedLen / 2;
            for (int i = 1; i + 1 < (int)runs.size(); i++)
                ans += runs[i].second / 2;
        } else {
            for (auto& r : runs)
                ans += r.second / 2;
        }
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
```
