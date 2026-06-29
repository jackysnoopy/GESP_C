# [NERC 2025] Doorway

## 题目描述

The construction of the doorway for the Nonsense Engineering and Research Convention was delegated to one of the future attendees, who decided on a multi-layered sliding door design.

Each layer can be described as a horizontal interval, bounded by solid walls on the left and right, containing a number of sliding doors of fixed lengths. Within a layer, each door can move independently to the left or right, as long as it does not overlap other doors or the walls. All layers are parallel and stacked vertically.

After construction, the organizers noticed a problem: it is difficult to fully open the door, and since a large number of attendees are expected, they need to create the largest possible opening to allow everyone to pass through freely.

The size of the opening is defined as the total length of horizontal intervals such that, at every point of such an interval and in every layer, there is neither a door nor a wall. Your task is to determine the largest possible opening, given the doors’ layout.

## 输入格式

The first line contains an integer $n$ ($1 \le n \le 100\,000$) — the number of layers of the door.

Each of the next $n$ lines starts with three integers $k_i$, $x_{i,1}$, $x_{i,2}$ ($0 \le k_i \le 300\,000$; $0 \le x_{i,1}  x_{i,2}$ are blocked by walls.

They are followed by $k_i$ integers $l_{i,1}, \dots, l_{i,k_i}$ ($1 \le l_{i,j}$; $\sum_{j=1}^{k_i} l_{i,j} \le x_{i,2} - x_{i,1}$) — the lengths of the sliding doors on that layer given in order from the leftmost door to the rightmost.

It is guaranteed that $\sum_{i=1}^{n} k_i \le 300\,000$.

## 输出格式

Output a single integer — the size of the largest possible opening that can be achieved by moving the sliding doors on each layer.

## 样例

### 样例输入 1
```
2
2 2 11 3 2
3 4 12 1 1 2
```

### 样例输出 1
```
4
```

### 样例输入 2
```
2
2 0 7 2 4
1 4 9 4
```

### 样例输出 2
```
0
```

## 提示

This illustration shows a solution for the first example. Walls are filled with black color, doors are filled with various shades of grey, the opening is white. When first doors on each layer are shifted to the left and the rest of the doors to the right, we get the largest opening of $4$.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/a6lelhuy.png)
:::

## 解题思路

### 问题分析

多层滑动门，每层有固定长度的门和墙壁。每层的门可以独立左右移动。求所有层同时打开的最大开口长度。

### 核心思路

每层的最大开口 = 总宽度 - 所有门的总长度。所有层的最大开口取最大值即为答案。

### 算法流程

1. 读入每层的墙壁范围 $[x_1, x_2]$ 和门的长度
2. 对每层计算：$max\_opening = (x_2 - x_1) - \sum l_{i,j}$
3. 取所有层的最大值作为答案

### 复杂度分析

- 时间复杂度：$O(\sum k_i)$
- 空间复杂度：$O(\sum k_i)$

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

    vector<int> k(n), x1(n), x2(n);
    vector<vector<int>> doors(n);

    for (int i = 0; i < n; i++) {
        cin >> k[i] >> x1[i] >> x2[i];
        doors[i].resize(k[i]);
        for (int j = 0; j < k[i]; j++) {
            cin >> doors[i][j];
        }
    }

    int total_doors = 0;
    for (int i = 0; i < n; i++) {
        total_doors += k[i];
    }

    if (total_doors == 0) {
        cout << "0\n";
        return 0;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int door_sum = 0;
        for (int j = 0; j < k[i]; j++) {
            door_sum += doors[i][j];
        }
        int max_opening = x2[i] - x1[i] - door_sum;
        ans = max(ans, max_opening);
    }

    cout << ans << "\n";
    return 0;
}
```
