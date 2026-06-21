# P13169 - [GCJ 2017 #1C] Parenting Partnering

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

### Sample 1
**Input:**
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

**Output:**
```
Case #1: 2
Case #2: 4
Case #3: 2
Case #4: 4
Case #5: 6
```

## 样例解释

**Sample Explanation**

Note that Cases #4 and #5 would not appear in the Small dataset.

Case #1 is the one described in the problem statement.

In Case #2, Jamie must cover for all of Cameron's activity time, and then Cameron must cover all the remaining time. This schedule entails four exchanges.

In Case #3, there is an exchange at midnight, from Cameron to Jamie. No matter how the parents divide up the remaining $1438$ non-activity minutes of the day, there must be at least one exchange from Jamie to Cameron, and there is no reason to add more exchanges than that.

In Case #4, note that back-to-back activities can exist for the same partner or different partners. There is no exchange at midnight because Cameron has activities both right before and right after that time. However, the schedule needs to add some time for Cameron in between Jamie's activities, requiring a total of $4$ exchanges. Notice that it is optimal to add a single interval for Cameron of length $718$ somewhere between minutes $2$ and $1438$, but the exact position of that added interval does not impact the number of exchanges, so there are multiple optimal schedules.

In Case #5, a possible optimal schedule is to assign Cameron to the intervals (in minutes) $100-200$, $500-620$, and $900-1400$.

## 数据范围

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

## 解题思路

### 问题分析

这道题是一个关于时间分配的问题。我们需要将一天（1440分钟）分配给两个人，每人恰好 720 分钟，同时最小化交换次数。

关键点：
1. 活动时间是固定的，不能改变
2. 空闲时间可以任意分配
3. 交换次数取决于颜色变化的边界

### 算法设计

1. **构建时间线**：将所有活动和空闲块按时间排序
2. **计算需求**：计算每个人还需要多少空闲时间
3. **分配空闲块**：使用暴力枚举或 DP 来分配空闲块
4. **计算交换次数**：根据分配方案计算交换次数

### 关键点

- 交换次数 = 颜色变化的次数
- 环形时间轴需要特殊处理（首尾连接）

## 算法原理

本题采用暴力枚举算法。由于测试集1的规模较小（AC+AJ <= 2），我们可以承受 $O(2^n)$ 的时间复杂度。

## 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Block {
    int start, end;
    int type; // 0: Cameron activity, 1: Jamie activity, 2: Free
};

bool compareBlocks(const Block& a, const Block& b) {
    return a.start < b.start;
}

int main() {
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int AC, AJ;
        cin >> AC >> AJ;
        
        vector<Block> blocks;
        
        for (int i = 0; i < AC; i++) {
            int C, D;
            cin >> C >> D;
            blocks.push_back({C, D, 0});
        }
        
        for (int i = 0; i < AJ; i++) {
            int J, K;
            cin >> J >> K;
            blocks.push_back({J, K, 1});
        }
        
        sort(blocks.begin(), blocks.end(), compareBlocks);
        
        vector<Block> timeline;
        int lastEnd = 0;
        
        for (const auto& b : blocks) {
            if (b.start > lastEnd) {
                timeline.push_back({lastEnd, b.start, 2});
            }
            timeline.push_back(b);
            lastEnd = b.end;
        }
        
        if (lastEnd < 1440) {
            timeline.push_back({lastEnd, 1440, 2});
        }
        
        int totalC = 0;
        for (const auto& b : timeline) {
            if (b.type == 0) totalC += (b.end - b.start);
        }
        
        int needC = 720 - totalC;
        
        vector<Block> freeBlocks;
        for (const auto& b : timeline) {
            if (b.type == 2) {
                freeBlocks.push_back(b);
            }
        }
        
        int minExchanges = INT_MAX;
        int numFree = freeBlocks.size();
        
        // 暴力枚举每个空闲块的归属
        for (int mask = 0; mask < (1 << numFree); mask++) {
            int cTime = 0;
            
            for (int i = 0; i < numFree; i++) {
                if (mask & (1 << i)) {
                    cTime += (freeBlocks[i].end - freeBlocks[i].start);
                }
            }
            
            if (cTime != needC) continue;
            
            // 构建颜色序列
            vector<int> colors;
            int freeIdx = 0;
            for (const auto& b : timeline) {
                if (b.type == 0) colors.push_back(0);
                else if (b.type == 1) colors.push_back(1);
                else {
                    colors.push_back((mask & (1 << freeIdx)) ? 0 : 1);
                    freeIdx++;
                }
            }
            
            int exchanges = 0;
            for (int i = 1; i < colors.size(); i++) {
                if (colors[i] != colors[i-1]) exchanges++;
            }
            if (colors.size() > 1 && colors[0] != colors.back()) exchanges++;
            
            minExchanges = min(minExchanges, exchanges);
        }
        
        cout << "Case #" << t << ": " << minExchanges << endl;
    }
    
    return 0;
}
```

## 复杂度分析

- **时间复杂度**：O(T * 2^N * N)，其中 N 是空闲块的数量
- **空间复杂度**：O(N)，用于存储时间块

## 注意事项

1. 这个暴力解法适用于测试集1（AC+AJ <= 2）
2. 对于测试集2，需要更高效的算法
3. 关键是正确处理环形时间轴和空闲块分配
