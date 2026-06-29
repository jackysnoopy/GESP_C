# [GCJ 2020 Qualification] Parenting Partnering Returns

## 题目描述

Cameron 和 Jamie 要分担 $N$ 项活动，每项活动在一天中的某个时间段进行。需要把每项活动分配给其中一人，使任何一人都不会同时负责两段重叠的活动。结束时刻为 $t$ 的活动与开始时刻为 $t$ 的活动**不算**重叠。

求任意一种合法分配方案；若不存在输出 `IMPOSSIBLE`。

## 输入格式

第一行 $T$。每组数据：第一行 $N$；接下来 $N$ 行，第 $i$ 行两个整数 $S_i, E_i$（活动起止时刻，距午夜分钟数）。

## 输出格式

对每组数据输出 `Case #x: y`，$y$ 为长度 $N$ 的字符串，第 $i$ 个字符为 `C`（Cameron）或 `J`（Jamie）；或 `IMPOSSIBLE`。

## 提示

**样例说明**：Case 2 三项活动两两重叠，无法分配；Case 4 任意分配都合法。

**数据范围**：$1 \le T \le 100$，$0 \le S_i < E_i \le 1440$，$2 \le N \le 1000$（Test Set 2）。

时间限制 20000ms，内存限制 1GB。

## 解题思路

### 问题分析

这是经典的区间图 2-染色问题：能否用两种颜色（C/J）给区间着色，使重叠区间异色。区间图是完美图，2-染色可行当且仅当任意时刻重叠区间数不超过 2。等价地，按开始时间贪心分配即可判断。

### 核心思路

**按开始时间排序后贪心**。维护两人各自的空闲时刻 `cEnd`、`jEnd`（即该人上一项活动结束时刻）。对每项活动（按开始时间）：
- 若 Cameron 空闲（$S \ge$ `cEnd`），分给 C，更新 `cEnd = E`；
- 否若 Jamie 空闲（$S \ge$ `jEnd`），分给 J，更新 `jEnd = E`；
- 否两人都在忙 → 存在 3 段重叠 → `IMPOSSIBLE`。

正确性：按开始时间处理，若某时刻两人都忙意味着当前活动与两人正在进行的活动都重叠，即 3 段重叠，必然无解；反之若总能分配则得到合法方案（每人的活动按结束时间不重叠，因为新分配的活动开始时刻 $\ge$ 该人上一次结束时刻）。注意用原始下标记录答案以按输入顺序输出。

### 算法流程

1. 读入活动，记录 $(S, E, \text{原下标})$，按 $S$ 升序排序。
2. `cEnd = jEnd = 0`，答案数组初始化。
3. 遍历排序后活动：优先分给空闲的 C，否则空闲的 J，否则标记不可行。
4. 按原下标填入 `C`/`J`，输出。

### 复杂度分析

- 时间复杂度：$O(N\log N)$（排序）。
- 空间复杂度：$O(N)$。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        vector<tuple<int,int,int>> act(N);
        for (int i = 0; i < N; i++) {
            int s, e;
            cin >> s >> e;
            act[i] = {s, e, i};
        }
        sort(act.begin(), act.end());
        int cEnd = 0, jEnd = 0;
        string ans(N, ' ');
        bool ok = true;
        for (auto& [s, e, idx] : act) {
            if (s >= cEnd) { ans[idx] = 'C'; cEnd = e; }
            else if (s >= jEnd) { ans[idx] = 'J'; jEnd = e; }
            else { ok = false; break; }
        }
        cout << "Case #" << tc << ": ";
        if (ok) cout << ans << "\n";
        else cout << "IMPOSSIBLE\n";
    }
    return 0;
}
```
