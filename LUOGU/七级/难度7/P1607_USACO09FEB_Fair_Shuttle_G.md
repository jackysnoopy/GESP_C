# [USACO09FEB] Fair Shuttle G

## 题目描述

 Farmer John 没有问题在集市周围走动来收集奖品或看表演，但他的牛却没有这么好的体力；在集市里走一整天会让它们筋疲力尽。为了帮助它们享受集市，FJ 安排了一辆穿梭卡车在集市的各个地点之间接送牛。

FJ 买不起真正好的穿梭车，所以他租的那辆只能沿着路线运行一次（！），并在沿途停靠 N（1 <= N <= 20,000）个站点（方便地编号为 1..N）。总共有 K（1 <= K <= 50,000）组牛，方便地编号为 1..K，希望乘坐穿梭车，每组 i 中的 M_i（1 <= M_i <= N）头牛想从站点 S_i（1 <= S_i < E_i）乘坐到更远的站点 E_i（S_i < E_i <= N）。

穿梭车可能无法接载整个小组的牛（因为它的容量有限），但可以适当地接载部分小组的牛。

给定穿梭车的容量 C（1 <= C <= 100）以及想要参观集市各个地点的牛群描述，确定在集市期间可以乘坐穿梭车的最大牛数。

## 输入格式

第一行：包含三个整数：K、N 和 C，用空格分隔。

第 2 行到第 K+1 行：在第 i+1 行中，会告诉你第 i 组牛的信息：S_i、E_i 和 M_i，用空格分隔。

## 输出格式

第一行：可以乘坐公交车的最大牛数。

## 样例

### 样例 1

**输入：**
```
8 15 3
1 5 2
13 14 1
5 8 3
8 14 2
14 15 1
9 12 1
12 15 2
4 6 1
```

**输出：**
```
10
```

## 提示

穿梭巴士可以从 1 到 5 接送 2 头牛，从 5 到 8 接送 3 头牛，从 8 到 14 接送 2 头牛，从 9 到 12 接送 1 头牛，从 13 到 14 接送 1 头牛，从 14 到 15 接送 1 头牛。

## 解题思路

### 问题分析

这是一个经典的区间调度问题，需要在容量限制下最大化运送的牛数。关键在于：
1. 穿梭车有固定容量 C
2. 每组牛有一个起始站和终点站
3. 需要决定每组接多少头牛

### 核心思路

**贪心算法：按终点排序**

1. 将所有牛组按终点 E_i 从小到大排序
2. 对于每个牛组，计算从起点到终点区间内的最大载重量
3. 如果还有容量，则接载 min(M_i, C - 最大载重量) 头牛
4. 使用差分数组高效维护载重量变化

**为什么按终点排序？**
- 终点越早的组，对后续组的影响越小
- 这样可以优先满足"短途"需求，为"长途"留出空间

### 算法流程

1. 读入 K 组牛的信息
2. 按终点 E_i 排序
3. 维护差分数组 diff，diff[i] 表示在站点 i 的载重量变化
4. 对于每组牛 (s, e, m)：
   - 计算区间 [s, e) 内的最大载重量 maxLoad
   - 接载 can = min(m, C - maxLoad) 头牛
   - 更新 diff[s] += can, diff[e] -= can
5. 累加所有接载的牛数

### 复杂度分析

- 时间复杂度：O(K * N)，其中 K 是组数，N 是站点数
- 空间复杂度：O(N)

## 参考代码

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, N, C;
    cin >> K >> N >> C;

    vector<tuple<int, int, int>> groups(K);
    for (int i = 0; i < K; i++) {
        int s, e, m;
        cin >> s >> e >> m;
        groups[i] = {e, s, m};
    }

    sort(groups.begin(), groups.end());

    vector<int> diff(N + 2, 0);
    int ans = 0;

    for (auto [e, s, m] : groups) {
        int maxLoad = 0;
        int cur = 0;
        for (int i = 1; i <= e; i++) {
            cur += diff[i];
            if (i >= s && i < e) {
                maxLoad = max(maxLoad, cur);
            }
        }
        int can = min(m, C - maxLoad);
        ans += can;
        diff[s] += can;
        diff[e] -= can;
    }

    cout << ans << "\n";
    return 0;
}
```
