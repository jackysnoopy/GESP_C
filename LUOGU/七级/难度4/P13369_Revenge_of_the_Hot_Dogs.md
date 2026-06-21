# [GCJ 2011 #1B] Revenge of the Hot Dogs

## 题目描述

Last year, several hot dog vendors were lined up along a street, and they had a tricky algorithm to spread themselves out. Unfortunately, the algorithm was very slow and they are still going. All is not lost though! The hot dog vendors have a plan: time to try a new algorithm!

The problem is that multiple vendors might be selling too close to each other, and then they will take each other's business. The vendors can move along the street at 1 meter/second. To avoid interfering with each other, they want to stand so that every pair of them is separated by a distance of at least $D$ meters.

Remember that the street is really long, so there is no danger of running out of space to move in either direction. Given the starting positions of all hot dog vendors, you should find the minimum time they need before all the vendors are separated (each two vendors are at least $D$ meters apart from each other).

## 输入格式

Each point of the street is labeled with a number, positive, negative or zero. A point labeled $p$ is $|p|$ meters east of the point labeled $0$ if $p$ is positive, and $|p|$ meters west of the point labeled $0$ if $p$ is negative. We will use this labeling system to describe the positions of the vendors in the input file.

The first line of the input file contains the number of cases, $T$. $T$ test cases follow. Each case begins with a line containing the number of points $C$ that have at least one hot dog vendor in the starting configuration and an integer $D$ -- the minimum distance they want to spread out to. The next $C$ lines each contain a pair of space-separated integers $P$, $V$, indicating that there are $V$ vendors at the point labeled $P$.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the minimum amount of time it will take for the vendors to spread out apart on the street. Answers with relative or absolute error of at most $10^{-6}$ will be accepted.

## 样例

--- Sample 1 ---
Input:
2
3 2
0 1
3 2
6 1
2 2
0 3
1 1
Output:

## 提示

**Limits**

- $1 \leq T \leq 50$.
- All the values $P$ are integers in the range $[-10^5, 10^5]$.
- Within each test case all $P$ values are distinct and given in an increasing order. The limit on the sum of $V$ values is listed below. All the $V$ values are positive integers.

**Small dataset (15 Pts, Test set 1 - Visible)**

- $1 \leq D \leq 5$
- $1 \leq C \leq 20$.
- The sum of all the $V$ values in one test case does not exceed $100$.
- Time limit: ~~30~~ 3 seconds.

**Large dataset (20 Pts, Test set 2 - Hidden)**

- $1 \leq D \leq 10^6$
- $1 \leq C \leq 200$.
- The sum of all $V$ values does not exceed $10^6$.
- Time limit: ~~60~~ 6 seconds.

## 解题思路

### 问题分析
- 街上若干热狗摊贩，可沿街以 1 m/s 移动，要求任意两摊相距 $\ge D$，街无限长。求使所有摊满足间隔的最短时间。
- 最短时间 $T$ 下，每个摊可在 $[x_i-T,x_i+T]$ 内重新定位，需选择互距 $\ge D$ 的位置。

### 核心思路
- 二分时间 $T$，检验可行性：按摊原始位置从左到右，贪心给每个摊分配尽量靠左且与前摊相距 $\ge D$ 的位置（约束在 $[x_i-T,x_i+T]$ 内）。
- 若某摊无法分配合法位置则 $T$ 不可行，增大二分下界。
- 二分到精度输出最小 $T$。

### 算法流程
1. 排序摊贩位置。
2. 二分 $T$，贪心分配位置检验。
3. 输出最小可行 $T$。

### 复杂度分析
- 时间复杂度：$O(N\log N+N\log(\text{精度}))$。
- 空间复杂度：$O(N)$。

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
        int C, D;
        cin >> C >> D;

        vector<pair<int, int>> vendors;
        for (int i = 0; i < C; i++) {
            int p, v;
            cin >> p >> v;
            for (int j = 0; j < v; j++) vendors.push_back({p, 0});
        }

        sort(vendors.begin(), vendors.end());
        int n = vendors.size();

        vector<int> target(n);
        for (int i = 0; i < n; i++) target[i] = i * D;

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, (long long)abs(vendors[i].first - target[i]));
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}

```
