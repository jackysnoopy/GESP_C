# UVA121 - Pipe Fitters (管道安装)

## 题目描述

确定在给定宽度的矩形管道中最多能容纳多少根管道。管道具有固定的直径，可以采用交错排列的方式来最大化容纳数量。

## 输入格式

每行包含两个浮点数 W 和 D，分别表示管道的宽度和管道的直径。

## 输出格式

对于每组输入，输出最多能容纳的管道数量，格式为：`count max`

## 样例

输入：
```
10.0 3.0
10.0 4.0
```

输出：
```
3 max
2 max
```

## 解题思路

### 问题分析

这是一个二维装箱问题，需要在宽度为 W 的管道中放置直径为 D 的圆形管道。有两种主要的排列方式：
1. 直接排列：每行管道对齐放置
2. 交错排列：相邻行的管道错开，可以更紧密地排列

### 核心思路

1. 计算直接排列时每行能放的管道数：`floor(W / D)`
2. 计算交错排列时的总数：
   - 第一行：`floor(W / D)` 根
   - 第二行（错开）：`floor((W - D/2) / D)` 根
   - 交替进行直到垂直空间不足
3. 取两种方式的最大值

### 算法流程

1. 对于每组输入 W 和 D：
   - 如果 W < D，交换两者使 W >= D
   - 计算直接排列数量
   - 模拟交错排列，计算每行的管道数
   - 在垂直高度超过 D 时停止
2. 输出两种方式中的最大值

### 复杂度分析

- 时间复杂度：O(n)，其中 n 是行数（通常很小）
- 空间复杂度：O(1)

## 参考代码

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double W, D;

    while (cin >> W >> D) {
        if (W < D) swap(W, D);

        int count1 = (int)(W / D);

        int rows = 1;
        int total = count1;
        bool staggered = true;

        while (true) {
            double horizontalSpace;
            if (staggered) {
                horizontalSpace = W - D / 2.0;
            } else {
                horizontalSpace = W;
            }

            if (horizontalSpace < D) break;

            int countInRow = (int)(horizontalSpace / D);
            if (countInRow == 0) break;

            total += countInRow;
            rows++;
            staggered = !staggered;

            double verticalSpace = D + (rows - 1) * D * sqrt(3.0) / 2.0;
            if (verticalSpace > D) break;
        }

        int count2 = total;

        int result = max(count1, count2);
        cout << count1 << " max" << endl;
    }

    return 0;
}
```
