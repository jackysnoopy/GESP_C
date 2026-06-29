# P13005 [GCJ 2022 Finals] Triangles

## 题目描述

You are given a set $P$ of $\mathbf{N}$ distinct points in the two-dimensional plane. You want to find a maximum set of triangles such that:
- Each vertex of a triangle in your set is a point from $P$ and each point in $P$ is a vertex of at most one triangle in your set.
- Each triangle in your set has positive area (i.e., its 3 vertices are not collinear).
- For any two sides of triangles in your set, their intersection is either empty or an endpoint of one of them.
- For any two triangles in your set, the intersection of the areas strictly inside those triangles is either empty or equal to one of them.

## 输入格式

第一行输入测试用例数量 $T$。每组测试用例以一行包含一个整数 $\mathbf{N}$ 开始，然后是 $\mathbf{N}$ 行，每行包含两个整数 $\mathbf{X}_i$ 和 $\mathbf{Y}_i$。

## 输出格式

对于每个测试用例，输出一行包含 `Case #x: y`，其中 $y$ 是最大三角形数量，然后是 $y$ 行，每行包含三个整数表示三角形的顶点。

## 样例

### 样例1
输入：
```
1
6
0 0
1 0
0 1
1 1
0 2
2 0
```
输出：
```
Case #1: 2
1 2 3
4 5 6
```

## 提示

$1 \leq T \leq 100$。

## 解题思路

### 问题分析

这是一个几何问题。需要找到最大三角形集合。

### 核心思路

**贪心匹配**：每次选择三个点形成三角形。

### 算法流程

```
对于每个测试用例:
    贪心选择三角形
    输出结果
```

### 复杂度分析

- **时间复杂度**：$O(N^3)$
- **空间复杂度**：$O(N)$

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
        int N;
        cin >> N;
        
        vector<int> X(N), Y(N);
        for (int i = 0; i < N; i++) {
            cin >> X[i] >> Y[i];
        }
        
        vector<bool> used(N, false);
        vector<tuple<int, int, int>> triangles;
        
        for (int i = 0; i < N; i++) {
            if (used[i]) continue;
            
            for (int j = i + 1; j < N; j++) {
                if (used[j]) continue;
                
                for (int k = j + 1; k < N; k++) {
                    if (used[k]) continue;
                    
                    long long cross = (long long)(X[j] - X[i]) * (Y[k] - Y[i]) - 
                                      (long long)(X[k] - X[i]) * (Y[j] - Y[i]);
                    
                    if (cross != 0) {
                        triangles.push_back({i + 1, j + 1, k + 1});
                        used[i] = true;
                        used[j] = true;
                        used[k] = true;
                        break;
                    }
                }
                
                if (used[i]) break;
            }
        }
        
        cout << "Case #" << t << ": " << triangles.size() << "\n";
        for (auto& [a, b, c] : triangles) {
            cout << a << " " << b << " " << c << "\n";
        }
    }
    
    return 0;
}
```
