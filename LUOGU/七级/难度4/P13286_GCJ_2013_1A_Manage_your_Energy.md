# [GCJ 2013 #1A] Manage your Energy

## 题目描述

You've got a very busy calendar today, full of important stuff to do. You worked hard to prepare and make sure all the activities don't overlap. Now it's morning, and you're worried that despite all of your enthusiasm, you won't have the energy to do all of this with full engagement.

You will have to manage your energy carefully. You start the day full of energy - $E$ joules of energy, to be precise. You know you can't go below zero joules, or you will drop from exhaustion. You can spend any non-negative, integer number of joules on each activity (you can spend zero, if you feel lazy), and after each activity you will regain $R$ joules of energy. No matter how lazy you are, however, you cannot have more than $E$ joules of energy at any time; any extra energy you would regain past that point is wasted.

Now, some things (like solving Code Jam problems) are more important than others. For the $i$th activity, you have a value $v_i$ that expresses how important this activity is to you. The gain you get from each activity is the value of the activity, multiplied by the amount of energy you spent on the activity (in joules). You want to manage your energy so that your total gain will be as large as possible.

Note that you cannot reorder the activities in your calendar. You just have to manage your energy as well as you can with the calendar you have.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case is described by two lines. The first contains three integers: $E$, the maximum (and initial) amount of energy, $R$, the amount you regain after each activity, and $N$, the number of activities planned for the day. The second line contains $N$ integers $v_i$, describing the values of the activities you have planned for today.

## 输出格式

For each test case, output one line containing "Case #x: $y$", where $x$ is the case number (starting from 1) and $y$ is the maximum gain you can achieve by managing your energy that day.

## 样例

### 样例输入 1
```
3
5 2 2
2 1
5 2 2
1 2
3 3 4
4 1 3 5
```

### 样例输出 1
```
Case #1: 12
Case #2: 12
Case #3: 39
```

## 提示

**Sample Explanation**

In the first case, we can spend all 5 joules of our energy on the first activity (for a gain of 10), regain 2 and spend them on the second activity. In the second case, we spend 2 joules on the first activity, regain them, and spend 5 on the second. In the third case, our regain rate is equal to the maximum energy, meaning we always recover all energy after each activity - so we can spend full 3 joules on each activity.

**Limits**

- $1 \leq T \leq 100 .$

**Small dataset (12 Pts, Test set 1 - Visible)**

- $1 \leq E \leq 5 .$
- $1 \leq R \leq 5 .$
- $1 \leq N \leq 10 .$
- $1 \leq v_{i} \leq 10 .$

**Large dataset (23 Pts, Test set 2 - Hidden)**

- $1 \leq E \leq 10^{7} .$
- $1 \leq R \leq 10^{7} .$
- $1 \leq N \leq 10^{4} .$
- $1 \leq v_{i} \leq 10^{7} .$

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
        long long E, R;
        int N;
        cin >> E >> R >> N;

        vector<long long> v(N);
        for (int i = 0; i < N; i++) cin >> v[i];

        long long ans = 0;
        long long energy = E;

        for (int i = 0; i < N; i++) {
            long long spend = energy;
            for (int j = i + 1; j < N; j++) {
                if (v[j] > v[i]) {
                    long long needed = max(0LL, E - R * (j - i));
                    spend = min(spend, energy - needed);
                }
            }
            spend = max(spend, 0LL);
            ans += spend * v[i];
            energy = min(E, energy - spend + R);
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析

初始有 E 焦耳能量，每完成一个活动后恢复 R 焦耳（不超过 E）。有 N 个按顺序排列的活动，第 i 个活动的价值为 v_i，收益 = 消耗能量 × v_i。求如何分配能量使总收益最大。

### 核心思路

贪心策略：对于当前活动 i，如果后续存在价值更高的活动 j（v[j] > v[i]），则需要为 j 保留足够的能量。需要保留的能量为 max(0, E - R × (j - i))，即在 j 到来时能恢复到 E 所需的最小剩余能量。当前活动的消耗 = min(当前能量, 当前能量 - 为未来保留的最小能量)。若后续无更高价值的活动，则全部消耗。

### 算法流程

1. 读入 E, R, N 和各活动价值 v[i]。
2. 初始化 energy = E, ans = 0。
3. 对每个活动 i：
   - 初始设定 spend = energy（全部消耗）。
   - 扫描后续所有活动 j：若 v[j] > v[i]，计算 needed = max(0, E - R × (j - i))，将 spend 限制为 min(spend, energy - needed)。
   - spend 取 max(spend, 0)，累加 spend × v[i] 到答案。
   - 更新 energy = min(E, energy - spend + R)。
4. 输出答案。

### 复杂度分析

- 时间复杂度：O(T × N²)，每个活动需扫描后续所有活动。
- 空间复杂度：O(N)，存储各活动价值。
