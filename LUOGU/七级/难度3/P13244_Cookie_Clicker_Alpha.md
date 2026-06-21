# [GCJ 2014 Qualification] Cookie Clicker Alpha

## 题目描述

你有 C 个农场，初始每秒生产 C 个饼干（至少 2 个）。
你可以花费 C 个农场来增加产量，每次增加 F 个农场的产量。
目标是获得 X 个饼干。每秒的产量是当前农场的数量。

求最短时间（秒）。

## 输入格式

第一行：C F X

## 输出格式

输出最短时间（精确到小数点后7位）

## 提示

数据范围：1 ≤ C ≤ 5000, 1 ≤ F ≤ 5000, 1 ≤ X ≤ 10^9

## 解题思路

### 问题分析
- 初始有 C 个农场，每秒生产 C 个饼干
- 可以花费 C 个时间来购买农场，每购买一个农场产量增加 F
- 目标是获得 X 个饼干
- 求最短时间

### 核心思路
**贪心策略**：
1. 在每个步骤，决定是继续等待还是购买农场
2. 如果继续等待获得 X 个饼干的时间 < 购买农场后再获得的时间，就不买
3. 否则，购买农场并继续

**数学计算**：
- 等待时间 = X / 当前产量
- 购买农场时间 = C / 当前产量 + X / (当前产量 + F)

### 算法流程
1. 读入 C, F, X
2. 当前产量 = 2.0
3. 总时间 = 0.0
4. 循环计算，直到等待时间优于购买农场时间
5. 输出精确到7位小数

### 复杂度分析
- 时间复杂度：O(需要购买的农场数)，理论上最坏情况是 O(log(目标))
- 空间复杂度：O(1)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double C, F, X;
    cin >> C >> F >> X;

    // Cookie Clicker Alpha：饼干点击者
    double rate = 2.0;
    double time = 0.0;

    while (true) {
        double current_time = X / rate;
        double new_time = C / rate + X / (rate + F);
        
        if (current_time <= new_time) {
            time += current_time;
            break;
        } else {
            time += C / rate;
            rate += F;
        }
    }

    cout << fixed << setprecision(7) << time << "\n";
    return 0;
}
```
