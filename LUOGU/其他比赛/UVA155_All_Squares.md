# UVA155 - All Squares (所有正方形)

## 题目描述

给定n个整数坐标点(x,y)，其中0<=x,y<=20，统计所有4个顶点都在给定点集中的正方形数量。

输入格式：
- 多个测试用例，以n=0结束
- 每个测试用例：第一行是n，接下来n行每行是x y坐标

输出要求：
- 对每个测试用例输出正方形数量

## 解题思路

### 问题分析

在二维整数网格上（0≤x,y≤20），给定若干点，需要找出所有正方形。正方形的4个顶点都必须在给定的点集中。

关键点：
- 正方形可以是任意大小和方向（不一定是轴对齐的）
- 需要避免重复计数同一个正方形
- 坐标范围较小（0-20），可以使用暴力枚举

### 核心思路

利用正方形的几何性质：
1. 对于任意两点，它们可以作为正方形的一条边
2. 给定一条边，可以通过向量旋转90度得到另外两个顶点
3. 向量(dx, dy)旋转±90度得到(-dy, dx)或(dy, -dx)

算法：
- 枚举所有点对作为潜在的边
- 对每条边，计算两个可能的正方形的另外两个顶点
- 检查这两个顶点是否都在点集中
- 使用规范表示（排序后的顶点列表）去重

### 算法流程

```
1. 读取点集，存入vector和set（便于快速查找）
2. 初始化正方形集合（用于去重）
3. 对每一对点(i, j)（i < j）：
   a. 计算向量(dx, dy) = (xj-xi, yj-yi)
   b. 方案1：旋转+90度，得到另外两个顶点
   c. 方案2：旋转-90度，得到另外两个顶点
   d. 检查坐标是否在有效范围内（0-20）
   e. 检查两个新顶点是否都在点集中
   f. 如果是，将4个顶点排序后加入正方形集合
4. 输出正方形集合的大小
```

### 复杂度分析

- 时间复杂度：O(n²)，其中n是点数（最多441个点，因为21×21网格）
- 空间复杂度：O(n + s)，其中s是正方形数量

## 代码实现

```cpp
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n != 0) {
        vector<Point> points(n);
        set<pair<int,int>> pointSet;
        
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
            pointSet.insert({points[i].x, points[i].y});
        }
        
        set<vector<pair<int,int>>> squares;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = points[i].x, y1 = points[i].y;
                int x2 = points[j].x, y2 = points[j].y;
                
                int dx = x2 - x1;
                int dy = y2 - y1;
                
                // Two possible squares for this edge
                // Square 1: rotate (dx, dy) by +90 degrees
                int nx1_1 = x2 - dy;
                int ny1_1 = y2 + dx;
                int nx2_1 = x1 - dy;
                int ny2_1 = y1 + dx;
                
                // Square 2: rotate (dx, dy) by -90 degrees
                int nx1_2 = x2 + dy;
                int ny1_2 = y2 - dx;
                int nx2_2 = x1 + dy;
                int ny2_2 = y1 - dx;
                
                // Check square 1
                if (nx1_1 >= 0 && nx1_1 <= 20 && ny1_1 >= 0 && ny1_1 <= 20 &&
                    nx2_1 >= 0 && nx2_1 <= 20 && ny2_1 >= 0 && ny2_1 <= 20) {
                    if (pointSet.count({nx1_1, ny1_1}) && pointSet.count({nx2_1, ny2_1})) {
                        vector<pair<int,int>> square = {
                            {x1, y1}, {x2, y2}, {nx1_1, ny1_1}, {nx2_1, ny2_1}
                        };
                        sort(square.begin(), square.end());
                        squares.insert(square);
                    }
                }
                
                // Check square 2
                if (nx1_2 >= 0 && nx1_2 <= 20 && ny1_2 >= 0 && ny1_2 <= 20 &&
                    nx2_2 >= 0 && nx2_2 <= 20 && ny2_2 >= 0 && ny2_2 <= 20) {
                    if (pointSet.count({nx1_2, ny1_2}) && pointSet.count({nx2_2, ny2_2})) {
                        vector<pair<int,int>> square = {
                            {x1, y1}, {x2, y2}, {nx1_2, ny1_2}, {nx2_2, ny2_2}
                        };
                        sort(square.begin(), square.end());
                        squares.insert(square);
                    }
                }
            }
        }
        
        cout << squares.size() << "\n";
    }
    
    return 0;
}
```

## 测试样例

**输入：**
```
7
0 0
0 1
1 0
1 1
2 0
2 1
0 2
8
0 0
0 1
1 0
1 1
2 0
2 1
0 2
2 2
0
```

**输出：**
```
1
2
```

**解释：**
- 第一个测试用例：7个点，可以组成1个正方形（(0,0), (0,1), (1,0), (1,1)）
- 第二个测试用例：8个点，可以组成2个正方形（小正方形和大正方形）

## 关键点

1. **向量旋转**：给定边向量(dx, dy)，旋转90度得到(-dy, dx)或(dy, -dx)
2. **去重**：使用排序后的顶点列表作为正方形的规范表示，存入set自动去重
3. **边界检查**：确保计算出的顶点坐标在0-20范围内
4. **快速查找**：使用set存储点，O(log n)时间检查点是否存在