# [TOPC 2023] Location, Location, Location

## 题目描述

The concept of “location, location, location” is a common phrase used in real estate and business to emphasize the importance of the physical location of a property or business. In real estate, it suggests that the desirability and value of a property are heavily influenced by its location, often more so than by the property’s features or condition. In business, it highlights that the success of a retail store or commercial establishment can be significantly impacted by its geographical location.

In recent years, people tend to buy electric vehicles, but the buyers soon find it is hard to install charging piles in their apartments or houses. Building a charging station can be a good idea to make a lot of money. Your boss, Lena, ask you to find a good location for establishing her charge station to serve the electric vehicle owners.

In recent times, there has been a growing trend towards the adoption of electric vehicles (EVs). However, many EV owners face the challenge of installing charging infrastructure in their apartments or houses. Establishing a charging station presents a lucrative opportunity in response to this demand. Your boss, Lena, has tasked you with identifying an optimal location for building a charging station to cater to the needs of electric vehicle owners.

You are given a list of $n$ locations represented as $(x, y)$ coordinates in a 2D plane. For each location, there is an apartment or a house without any charging infrastructure. Your task is to build a charging station at the location that is closest to all $n$ locations on the list. In this problem, distance is measured using the Manhattan distance metric. The Manhattan distance between two points $(x_1, y_1)$ and $(x_2, y_2)$ is defined as $|x_1 - x_2| + |y_1 - y_2|$. Your goal is to find a location $(x, y)$ such that the sum of the Manhattan distances from that location to all $n$ locations on the list is minimized.

## 输入格式

The first line contains a positive integer $n$ indicating the number of locations. The $i$-th of the $n$ following lines contains two integers $x_i$ and $y_i$. The coordinates of the $i$-th location is $(x_i, y_i)$.

## 输出格式

Print the location $(x, y)$ minimizing the sum of Manhattan distance from $(x, y)$ to all $n$ locations on the list. If there are multiple solutions, output the one minimizing $x$. If there still multiple solutions, output the one minimizing $y$.

## 样例

### 样例输入 1
```
4
3 1
0 2
2 3
1 0
```

### 样例输出 1
```
1 1
```

### 样例输入 2
```
2
0 0
2 2
```

### 样例输出 2
```
0 0
```

## 提示

- $1 \leq n \leq 100000$
- $-100000 \leq x_i \leq 100000$ for $1 \leq i \leq n$.
- $-100000 \leq y_i \leq 100000$ for $1 \leq i \leq n$.

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

    int n;
    cin >> n;

    vector<pair<int,int>> points(n);
    for (int i = 0; i < n; i++) cin >> points[i].first >> points[i].second;

    int minDist = 1e9;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int dx = points[i].first - points[j].first;
            int dy = points[i].second - points[j].second;
            minDist = min(minDist, dx*dx + dy*dy);
        }
    }

    cout << sqrt(minDist) << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
给定平面上 n 个点的坐标，要求找到一对点使得它们之间的欧几里得距离最小，并输出该距离。代码采用暴力枚举所有点对的方式求解。

### 核心思路
使用双重循环枚举所有点对 (i, j)，计算每对点之间的欧几里得距离的平方，维护最小值。最后对最小距离的平方取平方根输出。由于距离平方的最小值对应距离的最小值，可以避免开方运算的精度问题。

### 算法流程
1. 读入点的数量 n 和所有点的坐标
2. 初始化最小距离平方为一个较大的值
3. 使用双重循环枚举所有点对，计算距离平方并更新最小值
4. 对最小距离平方取平方根后输出

### 复杂度分析
- 时间复杂度：O(n²)，需要枚举所有点对
- 空间复杂度：O(n)，存储所有点的坐标
