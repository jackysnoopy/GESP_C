# [GCJ 2017 #1C] Parenting Partnering

## 题目描述

Cameron and Jamie are longtime life partners and have recently become parents! Being in charge of a baby, exciting as it is, is not without challenges. Given that both parents have a scientific mind, they have decided to take a scientific approach to baby care.

Cameron and Jamie are establishing a daily routine and need to decide who will be the main person in charge of the baby at each given time. They have been equal partners their whole relationship, and they do not want to stop now, so they decided that each of them will be in charge for exactly 12 hours (720 minutes) per day.

Cameron and Jamie have other activities that they either need or want to do on their own. Cameron has $A_C$ of these and Jamie has $A_J$. These activities always take place at the same times each day. None of Cameron's activities overlap with Jamie's activities, so at least one of the parents will always be free to take care of the baby.

Cameron and Jamie want to come up with a daily baby care schedule such that:

* Scheduled baby time must not interfere with a scheduled activity. That is, during Cameron's activities, Jamie has to be in charge of the baby, and vice versa.
* Each of Cameron and Jamie must have exactly 720 minutes assigned to them.
* The number of exchanges — that is, the number of times the person in charge of the baby changes from one partner to the other — must be as small as possible.

For example, suppose that Jamie and Cameron have a single activity each: Jamie has a morning activity from 9 am to 10 am, and Cameron has an afternoon activity from 2 pm to 3 pm. One possible but suboptimal schedule would be for Jamie to take care of the baby from midnight to 6 am and from noon to 6 pm, and for Cameron to take care of the baby from 6 am to noon and 6 pm to midnight. That fulfills the first two conditions, and requires a total of 4 exchanges, which happen at midnight, 6 am, noon and 6 pm. If there is an exchange happening at midnight, it is counted exactly once, not zero or two times.

A better option would be for Cameron to take care of the baby from midnight to noon, and Jamie to take care of the baby from noon to midnight. This schedule also fulfills the first two conditions, but it uses only 2 exchanges, which is the minimum possible.

Given Cameron's and Jamie's lists of activities, and the restrictions above, what is the minimum possible number of exchanges in a daily schedule?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a line containing two integers $A_C$ and $A_J$, the number of activities that Cameron and Jamie have, respectively. Then, $A_C + A_J$ lines follow. The first $A_C$ of these lines contain two integers $C_i$ and $D_i$ each. The $i$-th of Cameron's activities starts exactly $C_i$ minutes after the start of the day at midnight and ends exactly $D_i$ minutes after the start of the day at midnight (taking exactly $D_i - C_i$ minutes). The last $A_J$ of these lines contain two integers $J_i$ and $K_i$ each, representing the starting and ending time of one of Jamie's activities, in minutes counting from the start of the day at midnight (same format as Cameron's). No activity spans two days, and no two activities overlap (except that one might end exactly as another starts, but an exchange can still occur at that time).

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ the minimum possible number of exchanges, as described in the statement.

## 样例

### 样例输入 1
```
5
1 1
540 600
840 900
2 0
900 1260
180 540
1 1
1439 1440
0 1
2 2
0 1
1439 1440
1438 1439
1 2
3 4
0 10
1420 1440
90 100
550 600
900 950
100 150
1050 1400
```

### 样例输出 1
```
Case #1: 2
Case #2: 4
Case #3: 2
Case #4: 4
Case #5: 6
```

## 提示

**Sample Explanation**

Note that Cases #4 and #5 would not appear in the Small dataset.

Case #1 is the one described in the problem statement.

In Case #2, Jamie must cover for all of Cameron's activity time, and then Cameron must cover all the remaining time. This schedule entails four exchanges.

In Case #3, there is an exchange at midnight, from Cameron to Jamie. No matter how the parents divide up the remaining $1438$ non-activity minutes of the day, there must be at least one exchange from Jamie to Cameron, and there is no reason to add more exchanges than that.

In Case #4, note that back-to-back activities can exist for the same partner or different partners. There is no exchange at midnight because Cameron has activities both right before and right after that time. However, the schedule needs to add some time for Cameron in between Jamie's activities, requiring a total of $4$ exchanges. Notice that it is optimal to add a single interval for Cameron of length $718$ somewhere between minutes $2$ and $1438$, but the exact position of that added interval does not impact the number of exchanges, so there are multiple optimal schedules.

In Case #5, a possible optimal schedule is to assign Cameron to the intervals (in minutes) $100-200$, $500-620$, and $900-1400$.

**Limits**

- $1 \leq T \leq 100$.
- $0 \leq C_i < D_i \leq 24 \times 60$, for all $i$.
- $0 \leq J_i < K_i \leq 24 \times 60$, for all $i$.
- Any two of the intervals of $\{[C_i, D_i)\}$ for all $i$ union $\{[J_i, K_i)\}$ for all $i$ have an empty intersection. (The intervals are closed on the left and open on the right, which ensures that two exactly consecutive intervals have nothing in between but do not overlap.)
- $\sum (D_i - C_i)$ for all $i \leq 720$.
- $\sum (K_i - J_i)$ for all $i \leq 720$.

**Small dataset (Test Set 1 - Visible)**

- $0 \leq A_C \leq 2$.
- $0 \leq A_J \leq 2$.
- $1 \leq A_C + A_J \leq 2$.

**Large dataset (Test Set 2 - Hidden)**

- $0 \leq A_C \leq 100$.
- $0 \leq A_J \leq 100$.
- $1 \leq A_C + A_J \leq 200$.

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
        int AC, AJ;
        cin >> AC >> AJ;

        vector<pair<int, int>> cameron, jamie;
        for (int i = 0; i < AC; i++) {
            int c, d;
            cin >> c >> d;
            cameron.push_back({c, d});
        }
        for (int i = 0; i < AJ; i++) {
            int j, k;
            cin >> j >> k;
            jamie.push_back({j, k});
        }

        vector<pair<int, int>> all;
        for (auto& p : cameron) all.push_back(p);
        for (auto& p : jamie) all.push_back(p);
        sort(all.begin(), all.end());

        int exchanges = 2;
        for (int i = 1; i < (int)all.size(); i++) {
            if (all[i].first > all[i - 1].second) exchanges += 2;
        }

        cout << "Case #" << t << ": " << exchanges << "\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析
给定两人（Cameron 和 Jamie）的活动时间表，两人需各负责照看婴儿恰好 720 分钟。活动期间对方必须负责照看。要求最小化交接（exchanges）次数，即负责人切换的次数。

### 核心思路
将所有活动（不论属于谁）按时间排序后，相邻活动之间的空隙需要由另一方来填充。每次空隙前后都是同一个人的活动时，填充该空隙需要 2 次交接（进入和离开）。初始交接次数为 2（因为一天是环形的，至少需要 2 次交接才能让两人各负责一半时间）。

### 算法流程
1. 读入 Cameron 和 Jamie 的所有活动时间区间
2. 将所有活动合并为一个列表，按起始时间排序
3. 初始化交接次数为 2（环形日程的基本交接）
4. 遍历排序后的活动列表，若相邻两个活动之间存在空隙（前一个活动结束时间 < 后一个活动起始时间），则交接次数加 2
5. 输出最终的交接次数

### 复杂度分析
- 时间复杂度：O((A_C + A_J) log(A_C + A_J))，主要来自排序操作
- 空间复杂度：O(A_C + A_J)，用于存储所有活动区间
