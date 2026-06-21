# [GKS 2020 #F] Metal Harvest

## 题目描述

You are in charge of deploying robots to harvest Kickium from a nearby asteroid. Robots are not designed to work as a team, so only $1$ robot can harvest at any point of time. A single robot can be deployed for up to $K$ units of time in a row before it returns for calibration, regardless of how much time it spends on harvesting during that period. Harvesting can only be done during specific time intervals. These time intervals do not overlap. Given $K$ and the time intervals in which harvesting is allowed, what is the minimum number of robot deployments required to harvest at all possible times?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow.

The first line of each test case gives two space separated integers $N$ and $K$: the number of time intervals in which harvesting is allowed, and the maximum duration a robot can be deployed for before returning for calibration.

The next $N$ lines contain a pair of space separated integers $S_i$ and $E_i$: the start time and the end time of the $i$-th interval respectively. Please note that intervals don't include the time unit starting at the moment $E_i$, so for example an interval with $(S_i = 2; E_i = 5)$ has duration of $3$ time units.

## 输出格式

For each test case, output one line containing `Case #`$x$`: `$y$`, where $x$ is the test case number (starting from $1$) and $y$ is the number of times robot deployment is needed so that for each interval there is one robot harvesting at that time.

## 样例

### 样例输入 1
```
2
3 5
1 5
10 11
8 9
3 2
1 2
3 5
13 14
```

### 样例输出 1
```
Case #1: 2
Case #2: 3
```

## 提示

In Sample Case #$1$, we deploy the robot at time instant $1$ and it becomes available for the interval $[1, 6]$. However, it harvests only for the time range $[1, 5]$. After that we deploy the robot at $6$ and it becomes available for the time interval $[6, 11]$. This deployment covers both the remaining intervals $[8, 9]$ and $[10, 11]$. There are multiple optimal strategies here. For example, we can deploy the $2$nd robot at $7$. It would then cover the range $[7, 12]$, thus harvesting for the intervals $[8, 9]$ and $[10, 11]$.

In Sample Case #$2$, we deploy the robot at time instant $1$, and it becomes available for $[1, 3]$, but harvests for $[1, 2]$ as $[2, 3]$ is not part of any interval. After that we deploy the robot at $3$ for the time range $[3, 5]$ in which the robot harvests for the interval $[3, 5]$. The $3$rd deployment is done at time instant $13$ making the robot available for time range $[13, 15]$. However, it harvests only for the interval $[13, 14]$. Thus $3$ deployments are needed to cover all the intervals.

### Limits

$1 \le T \le 100$.

All $S_i$ are distinct.

For any two intervals $(S_i, E_i)$ and $(S_j, E_j)$ with $S_i < S_j$, $E_i < S_j$.

**Test Set $1$**

$1 \le N \le 100$.

$1 \le K \le 100$.

$1 \le S_i < E_i \le 200$.

**Test Set $2$**

$100 < N \le 10^5$, in at most $10$ test cases.

$1 \le N \le 100$, in the remaining test cases.

$1 \le K \le 10^9$.

$1 \le S_i < E_i \le 10^9$.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> harvest(n);
    for (int i = 0; i < n; i++) cin >> harvest[i];

    int ans = 0;
    for (int h : harvest) ans += h;

    cout << ans << "\n";
    return 0;
}
```
