# [GCJ 2012 #1A] Kingdom Rush

## 题目描述

Kingdom Rush was created by Ironhide Game Studio. Ironhide Game Studio does not endorse and has no involvement with Google Code Jam.

Ryan is playing Kingdom Rush, a single-player tower defense game developed by Ironhide Game Studio. In Kingdom Rush, players earn stars by completing levels, in a way described below. Having more stars makes the player more powerful; so while Ryan might not be able to complete level 2 right away, he might be able to complete it after earning stars from level 1.

The real game Kingdom Rush doesn't work in quite the same way as this problem. It isn't important to have played the game in order to solve the problem.

In this problem's version of Kingdom Rush, when a player completes a level, he or she is given a 1-star rating or a 2-star rating. That rating might allow the player to earn stars as follows:

* If the player has never completed the level before and completes it with a 1-star rating, that player earns 1 star.
* If the player has never completed the level before and completes it with a 2-star rating, that player earns 2 stars.
* If the player has only completed the level before with a 1-star rating and completes it this time with a 2-star rating, the player earns 1 more star.

Otherwise there is no way for a player to earn stars.

Ryan might not be able to complete every level right away. For each level, before he can complete it with a 1-star rating, he needs to have earned a certain number of stars; and he will need a larger or equal number of stars to complete that level with a 2-star rating.

For example, suppose there are two levels:

* Level 1 requires 0 stars to complete with a 1-star rating, and 1 star to complete with a 2-star rating.
* Level 2 requires 0 stars to complete with a 1-star rating, and 2 stars to complete with a 2-star rating.

Here's a possible series of events for Ryan:

1. Ryan starts with 0 stars. He can choose to complete either level 1 or level 2 with a 1-star rating. He chooses to complete level 1 with a 1-star rating. Now he has 1 star.
2. Now Ryan can either complete level 2 with a 1-star rating, or level 1 with a 2-star rating. He chooses to complete level 1 with a 2-star rating. Now he has 2 stars.
3. Now Ryan can complete level 2 with a 2-star rating. He does that, and now he has 4 stars.
4. Now he is done, having completed all levels with 2-star ratings and earned 4 stars (2 per level). He has completed levels 3 times: level 1 twice, and level 2 once.

Ryan is great at tower defense games, but he needs some help to beat Kingdom Rush as quickly as possible. Your job is to figure out how many times he needs to complete levels in order to earn a 2-star rating on every level.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a line containing a single integer $N$, indicating how many levels are in the game. $N$ lines follow. The $i$th line contains two integers $a_i$ and $b_i$: the number of stars it takes to earn a one-star rating or a two-star rating, respectively, on level $i$.

## 输出格式

For each test case, output one line containing "Case #x: y", where $x$ is the case number (starting from 1) and $y$ is the minimum number of times Ryan must complete levels in order to have earned a 2-star rating on every level. If it is impossible for Ryan to earn a 2-star rating on every level, $y$ should instead be the string "Too Bad" (without the " characters, but with that exact capitalization). This indicates that Ryan is too bad at Kingdom Rush to finish the whole game.

## 样例

### 样例输入 1
```
4
2
0 1
0 2
3
2 2
0 0
4 4
1
1 1
5
0 5
0 1
1 1
4 7
5 6
```

### 样例输出 1
```
Case #1: 3
Case #2: 3
Case #3: Too Bad
Case #4: 6
```

## 提示

**Limits**

- $1 \leq T \leq 100$.
- $0 \leq a_i \leq b_i \leq 2001$.

**Test set 1 (15 Pts, Visible Verdict)**

- $1 \leq N \leq 10$.

**Test set 2 (18 Pts, Hidden Verdict)**

- $1 \leq N \leq 1000$.

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
        cin >> N;

        vector<pair<int, int>> levels(N);
        for (int i = 0; i < N; i++) cin >> levels[i].first >> levels[i].second;

        sort(levels.begin(), levels.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });

        int stars = 0;
        int games = 0;
        vector<bool> done(N, false);

        while (true) {
            bool found = false;
            for (int i = 0; i < N; i++) {
                if (!done[i] && stars >= levels[i].second) {
                    stars += (done[i] ? 1 : 2);
                    done[i] = true;
                    games++;
                    found = true;
                    break;
                }
            }
            if (found) continue;

            for (int i = 0; i < N; i++) {
                if (!done[i] && stars >= levels[i].first) {
                    stars += 1;
                    done[i] = true;
                    games++;
                    found = true;
                    break;
                }
            }
            if (!found) break;
        }

        bool all_done = true;
        for (int i = 0; i < N; i++) {
            if (!done[i]) {
                all_done = false;
                break;
            }
        }

        cout << "Case #" << t << ": ";
        if (all_done) cout << games << "\n";
        else cout << "Too Bad\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析
每个关卡需要一定数量的星星才能以 1 星或 2 星评级通关。目标是让所有关卡都达到 2 星评级，求最少通关次数。

### 核心思路
贪心策略：按 2 星要求 $b_i$ 从小到大排序。每轮操作中：
1. 优先选择可以一次性拿到 2 星的关卡（当前星星数 $\geq b_i$）
2. 若无此类关卡，则选择可以拿 1 星的关卡（当前星星数 $\geq a_i$）
3. 重复直到无法继续

这种贪心的正确性在于：优先完成低要求的关卡能尽早获得更多星星，从而解锁更高要求的关卡。

### 算法流程
1. 读入所有关卡的 $(a_i, b_i)$ 要求
2. 按 $b_i$ 升序排序
3. 循环执行：
   - 遍历找可直接 2 星通关的关卡，完成并获得 2 星
   - 若无，遍历找可 1 星通关的关卡，完成并获得 1 星
   - 若两者都无，退出循环
4. 检查是否所有关卡都已完成，输出结果

### 复杂度分析
- **时间复杂度**：$O(N^2)$，外层循环最多 $2N$ 次，内层遍历 $N$ 个关卡
- **空间复杂度**：$O(N)$，存储关卡信息和完成状态
