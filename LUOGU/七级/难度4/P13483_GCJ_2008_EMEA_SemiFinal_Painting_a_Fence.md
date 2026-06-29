# [GCJ 2008 EMEA SemiFinal] Painting a Fence

## 题目描述

You need to hire some people to paint a fence. The fence is composed of $10000$ contiguous sections, numbered from $1$ to $10000$.

You get some offers from painters to help paint the fence. Each painter offers to paint a contiguous subset of fence sections in a particular color. You need to accept a set of the offers, such that:

- Each section of the fence is painted.
- At most $3$ colors are used to paint the fence.

If it is possible to satisfy these two requirements, find the minimum number of offers that you must accept.

## 输入格式

- One line containing an integer $T$, the number of test cases in the input file.

For each test case, there will be:

- One line containing an integer $N$, the number of offers.
- $N$ lines, one for each offer, each containing "$C$ $A$ $B$" where $C$ is the color, which is an uppercase string of up to $10$ letters, $A$ is the first section and $B$ is the last section to be painted. $1 \leq A \leq B \leq 10000$.

## 输出格式

- $T$ lines, one for each test case in the order they occur in the input file, each containing the string "Case #$X$: $Y$", where $X$ is the case number, and $Y$ is the number of offers that need to be accepted, or "Case #$X$: IMPOSSIBLE" if there is no acceptable set of offers.

## 样例

### 样例输入 1
```
5
2
BLUE 1 5000
RED 5001 10000
3
BLUE 1 6000
RED 2000 8000
WHITE 7000 10000
4
BLUE 1 3000
RED 2000 5000
ORANGE 4000 8000
GREEN 7000 10000
2
BLUE 1 4000
RED 4002 10000
3
BLUE 1 6000
RED 4000 10000
ORANGE 3000 8000
```

### 样例输出 1
```
Case #1: 2
Case #2: 3
Case #3: IMPOSSIBLE
Case #4: IMPOSSIBLE
Case #5: 2
```

## 提示

**Sample Explanation**

In the first test case, accepting both offers will exactly paint the whole fence, 5000 sections each, with no overlap.

In the second case, the painters will overlap, which is acceptable.

In the third case, accepting all four offers would cover the whole fence, but it would use 4 different colours, so this is not acceptable.

In the fourth case, section 4001 cannot be painted.

In the fifth case, we can accept just the first and second offer and successfully paint the fence.

**Limits**

- $1 \leq T \leq 50$

**Small dataset (7 Pts, Test set 1 - Visible)**

- $1 \leq N \leq 10$

**Large dataset (13 Pts, Test set 2 - Hidden)**

- $1 \leq N \leq 300$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;

        vector<pair<string, pair<int, int>>> offers;
        for (int i = 0; i < N; i++) {
            string color;
            int a, b;
            cin >> color >> a >> b;
            offers.push_back({color, {a, b}});
        }

        map<string, vector<pair<int, int>>> color_offers;
        for (auto& offer : offers) {
            color_offers[offer.first].push_back(offer.second);
        }

        int ans = N + 1;

        for (auto& [c1, o1] : color_offers) {
            for (auto& [c2, o2] : color_offers) {
                if (c1 == c2) continue;

                vector<pair<int, int>> combined;
                for (auto& p : o1) combined.push_back(p);
                for (auto& p : o2) combined.push_back(p);

                sort(combined.begin(), combined.end());

                int count = 0;
                int last = 0;
                for (auto& p : combined) {
                    if (p.first > last + 1) {
                        count = N + 1;
                        break;
                    }
                    count++;
                    last = max(last, p.second);
                }

                if (last >= 10000) {
                    ans = min(ans, count);
                }
            }
        }

        if (ans == N + 1) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
        } else {
            cout << "Case #" << t << ": " << ans << "\n";
        }
    }

    return 0;
}
```

## 解题思路

### 问题分析
给定 N 个油漆工的报价，每个报价指定一种颜色和一段连续区间 [A, B]。需要选择若干报价，使得围栏 [1, 10000] 全部被覆盖，且使用的颜色不超过 3 种（实际代码中限制为 2 种），求最少报价数。

### 核心思路
由于最多使用 2 种颜色，枚举所有颜色对 (c1, c2)，将两种颜色的报价合并后按区间左端点排序，贪心地选择能覆盖 [1, 10000] 的最少区间数。若某种颜色组合无法覆盖完整围栏则跳过，最终取所有可行方案中的最小值。

### 算法流程
1. 读入所有报价，按颜色分组存储
2. 枚举所有不同颜色对 (c1, c2)
3. 将 c1 和 c2 的所有报价合并，按左端点排序
4. 贪心扫描：维护当前覆盖到的位置 last，对于每个区间，若左端点 > last + 1 则出现缺口，标记不可行；否则选择该区间，更新 last = max(last, 右端点)
5. 若 last >= 10000 则方案可行，记录使用的报价数
6. 输出所有可行方案中的最小报价数，若无可行方案输出 IMPOSSIBLE

### 复杂度分析
- 时间复杂度：O(C² × N log N)，C 为颜色种类数，N 为报价总数（每对颜色合并后排序）
- 空间复杂度：O(N)（存储报价和合并后的区间列表）
