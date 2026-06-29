# [ICPC 2018 Yokohama R] Emergency Evacuation

## 题目描述

The Japanese government plans to increase the number of inbound tourists to forty million in the year $2020$, and sixty million in $2030$. Not only increasing touristic appeal but also developing tourism infrastructure further is indispensable to accomplish such numbers.

One possible enhancement on transport is providing cars extremely long and/or wide, carrying many passengers at a time. Too large a car, however, may require too long to evacuate all passengers in an emergency. You are requested to help estimating the time required.

The car is assumed to have the following seat arrangement.

- A center aisle goes straight through the car, directly connecting to the emergency exit door at the rear center of the car.
- The rows of the same number of passenger seats are on both sides of the aisle.

A rough estimation requested is based on a simple step-wise model. All passengers are initially on a distinct seat, and they can make one of the following moves in each step.

- Passengers on a seat can move to an adjacent seat toward the aisle. Passengers on a seat adjacent to the aisle can move sideways directly to the aisle.
- Passengers on the aisle can move backward by one row of seats. If the passenger is in front of the emergency exit, that is, by the rear-most seat rows, he/she can get off the car.

The seat or the aisle position to move to must be empty; either no other passenger is there before the step, or the passenger there empties the seat by moving to another position in the same step. When two or more passengers satisfy the condition for the same position, only one of them can move, keeping the others wait in their original positions.

The leftmost figure of Figure C.1 depicts the seat arrangement of a small car given in Sample Input 1. The car have five rows of seats, two seats each on both sides of the aisle, totaling twenty. The initial positions of seven passengers on board are also shown.

The two other figures of Figure C.1 show possible positions of passengers after the first and the second steps. Passenger movements are indicated by fat arrows. Note that, two of the passengers in the front seat had to wait for a vacancy in the first step, and one in the second row had to wait in the next step.

Your task is to write a program that gives the smallest possible number of steps for all the passengers to get off the car, given the seat arrangement and passengers' initial positions.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/x3p3lfi8.png)

Figure C.1. Simple Model
:::

## 输入格式

The input consists of a single test case of the following format.

$$
\begin{aligned}
& r \quad s \quad p \\
& i_1 \quad j_1 \\
& \vdots \\
& i_p \quad j_p
\end{aligned}
$$

Here, $r$ is the number of passenger seat rows, $s$ is the number of seats on each side of the aisle, and $p$ is the number of passengers. They are integers satisfying $1 \leq r \leq 500$, $1 \leq s \leq 500$, and $1 \leq p \leq 2rs$.

The following $p$ lines give initial seat positions of the passengers. The $k$-th line with $i_k$ and $j_k$ means that the $k$-th passenger's seat is in the $i_k$-th seat row and it is the $j_k$-th seat on that row. Here, rows and seats are counted from front to rear and left to right, both starting from one. They satisfy $1 \leq i_k \leq r$ and $1 \leq j_k \leq 2s$. Passengers are on distinct seats, that is, $i_k \neq i_l$ or $j_k \neq j_l$ holds if $k \neq l$.

## 输出格式

The output should be one line containing a single integer, the minimum number of steps required for all the passengers to get off the car.

## 样例

### 样例输入 1
```
5 2 7
1 1
1 2
1 3
2 3
2 4
4 4
5 2
```

### 样例输出 1
```
9
```

### 样例输入 2
```
500 500 16
1 1
1 2
1 999
1 1000
2 1
2 2
2 999
2 1000
3 1
3 2
3 999
3 1000
499 500
499 501
499 999
499 1000
```

### 样例输出 2
```
1008
```

## 提示

难度：普及/提高−

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r, c;
    cin >> n >> r >> c;

    vector<pair<int,int>> seats(n);
    for (int i = 0; i < n; i++) cin >> seats[i].first >> seats[i].second;

    int ans = 0;
    for (auto [x, y] : seats) {
        ans = max(ans, abs(x - r) + abs(y - c));
    }

    cout << ans << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
一辆车有 r 排座位，每排两侧各有 s 个座位，中间是过道。紧急出口在车尾中央。乘客需要从座位移动到过道，再沿过道向后走到出口下车。目标是求所有乘客全部下车所需的最少步数。

### 核心思路
参考代码的逻辑是：对每个乘客，计算其座位到出口位置 (r, c) 的曼哈顿距离（即 |x - r| + |y - c|），取所有乘客中该距离的最大值作为答案。其思想是：每个乘客独立移动到出口的最短路径就是曼哈顿距离，而所有乘客同时移动时，最慢的那个乘客决定了总时间。因此答案就是所有乘客中最远的那个到出口的距离。

### 算法流程
1. 读入排数 r、每侧座位数 s、乘客数 n
2. 读入出口位置 (r, c)（代码中 c 为过道列号）
3. 读入每个乘客的座位坐标 (x, y)
4. 对每个乘客计算曼哈顿距离 |x - r| + |y - c|
5. 取所有距离的最大值作为答案输出

### 复杂度分析
- 时间复杂度：O(n)，遍历所有乘客计算距离
- 空间复杂度：O(n)，存储乘客座位坐标
