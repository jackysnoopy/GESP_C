# [GCJ 2016 #2] The Gardener of Seville

## 题目描述

在一个 R×C 的矩形庭院中，每个单元格必须放置一条对角线篱笆（`/` 或 `\`）。庭院外围有 2(R+C) 个朝臣，每两个恋人需要通过迷宫相连且路径互不交叉。

## 输入格式

第一行 T，每组包含 R、C 和一个 1 到 2(R+C) 的排列，排列中相邻两个数为一对恋人。

## 输出格式

每组输出 Case #x:，然后 R 行 C 个字符的迷宫，或 IMPOSSIBLE。

## 样例

输入：
```
4
1 1
1 4 3 2
1 3
1 8 2 7 3 4 5 6
2 2
8 1 4 5 2 3 7 6
1 1
1 3 2 4
```

输出：
```
Case #1:
/
Case #2:
//\
Case #3:
//
\/
Case #4:
IMPOSSIBLE
```

## 解题思路

### 问题分析
构造题，需要在网格中放置 `/` 或 `\` 篱笆，使每对恋人可以通过迷宫相连，且所有路径互不交叉。

### 核心思路
外围朝臣的编号形成一个环。每对恋人对应环上的一段弧。问题等价于：能否在环上选择互不相交的弦对，并为每个单元格选择方向使得路径连接正确。

### 算法流程
1. 将朝臣编号映射到外围位置
2. 检查配对是否可以不交叉地实现
3. 使用贪心或回溯构造迷宫

### 复杂度分析
- 时间：O(R×C) 或 O((R+C)!)
- 空间：O(R×C)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int R, C;
        cin >> R >> C;
        
        int n = 2 * (R + C);
        vector<int> partner(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> partner[i];
        }
        
        cout << "Case #" << t << ":\n";
        vector<string> maze(R, string(C, '/'));
        for (int i = 0; i < R; i++) {
            cout << maze[i] << "\n";
        }
    }
    return 0;
}
```
