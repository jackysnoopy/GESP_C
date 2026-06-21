# [USACO19FEB] Painting The Barn S

## 题目描述

农夫约翰不擅长多任务处理。他经常分心，很难完成长的项目。目前，他正试图在谷仓的一侧上漆，但他一直在画小矩形区域，然后由于照料奶牛的需要而偏离了方向，使得谷仓的某些部分上漆的涂料比其他部分多。

我们可以将谷仓的一侧描述为一个二维 $x-y$ 平面，农夫约翰在该平面上绘制 $n$ 个矩形，每个矩形的边都与坐标轴平行，每个矩形由谷仓的左下角和右上角点的坐标描述。

农夫约翰想在谷仓上涂几层油漆，这样在不久的将来就不需要再重新粉刷了。但是，他不想浪费时间涂太多的油漆。结果表明，$K$ 涂层是最佳用量。请在他画完所有的长方形后，帮他确定谷仓有多少面积被 $K$ 层油漆覆盖。

## 输入格式

输入的第一行包含 $n$ 和 $K$。

其余 $n$ 行中的每一行包含四个整数 $x_1$、$y_1$、$x_2$、$y_2$，描述正在绘制的矩形区域，左下角 $(x_1,y_1)$ 和右上角 $(x_2,y_2)$。所有 $x$ 和 $y$ 值都在 $0$ 到 $1000$ 范围内，并且所有矩形都有正面积。

## 输出格式

请输出谷仓被 $K$ 层油漆覆盖的区域。

## 样例 #1

**输入**
```
3 2
1 1 5 5
4 4 7 6
3 3 8 7
```

**输出**
```
8
```

## 提示

$1\le K\le n\le 10^5$。

USACO 2019 二月月赛银牌组第二题。

## 解题思路

### 问题分析

$N$ 个矩形，每个矩形区域覆盖一层涂料。求恰好被覆盖 $K$ 层的格子总面积。坐标范围可达 $1000$ 级别。

### 核心思路

**二维差分 + 坐标离散化。** 由于坐标范围可能很大但矩形数量较少，使用坐标压缩将稀疏坐标映射到连续整数，然后在压缩后的网格上做二维差分。

每个矩形 $(x_1,y_1,x_2,y_2)$ 覆盖 $[x_1,x_2) \times [y_1,y_2)$ 区域。注意是左闭右开。

### 算法流程

1. 收集所有矩形的 $x$ 和 $y$ 坐标，排序去重得到压缩后的坐标序列。
2. 在压缩后的网格上做二维差分。
3. 恢复后找出值等于 $K$ 的格子，计算其对应的原始面积并累加。

### 复杂度分析

- **时间复杂度：** $O(N^2)$（最坏），但实际随矩形数线性。
- **空间复杂度：** $O(N^2)$。

### 要点

- 坐标离散化后，压缩坐标 $i$ 对应的线段长为 $\text{xs}[i] - \text{xs}[i-1]$。
- 注意矩形是左闭右开的 $[x_1,x_2) \times [y_1,y_2)$，这在离散化后需要正确处理。
- 二维差分的四个标记点不要搞混。

## 参考代码
## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    cin >> N >> K;
    vector<array<int,4>> rect(N);
    vector<int> xs, ys;
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rect[i] = {x1, y1, x2, y2};
        xs.push_back(x1); xs.push_back(x2);
        ys.push_back(y1); ys.push_back(y2);
    }
    sort(xs.begin(), xs.end()); xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end()); ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int nx = xs.size(), ny = ys.size();
    vector<vector<int>> d(nx + 2, vector<int>(ny + 2, 0));
    for (auto &r : rect) {
        int x1 = lower_bound(xs.begin(), xs.end(), r[0]) - xs.begin() + 1;
        int y1 = lower_bound(ys.begin(), ys.end(), r[1]) - ys.begin() + 1;
        int x2 = lower_bound(xs.begin(), xs.end(), r[2]) - xs.begin() + 1;
        int y2 = lower_bound(ys.begin(), ys.end(), r[3]) - ys.begin() + 1;
        d[x1][y1]++; d[x1][y2+1]--; d[x2+1][y1]--; d[x2+1][y2+1]++;
    }
    long long ans = 0;
    for (int i = 1; i <= nx; i++) {
        for (int j = 1; j <= ny; j++) {
            d[i][j] += d[i-1][j] + d[i][j-1] - d[i-1][j-1];
            if (d[i][j] == K)
                ans += (long long)(xs[i-1] - xs[i-2]) * (ys[j-1] - ys[j-2]);
        }
    }
    cout << ans << "\n";
    return 0;
}
```
