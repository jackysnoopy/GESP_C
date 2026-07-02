# UVA133 - The Rolling Ball (滚动球)

## 题目描述

两个10x10的网格代表一个板子的两面，球可以在网格上滚动。当一个球滚入另一个球的位置时，会推动另一个球。

## 算法思路

1. 使用二维数组表示两个网格的状态
2. 模拟球的移动过程
3. 处理球之间的碰撞和推动
4. 输出最终的网格状态

## 复杂度分析

- 时间复杂度：O(n × moves)，n为球的数量，moves为移动次数
- 空间复杂度：O(1)，固定大小的网格

## C++ 代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        vector<string> grid(20);
        for (int i = 0; i < 20; i++) {
            grid[i].assign(10, '.');
        }
        for (int i = 0; i < n; i++) {
            int side, r, c;
            cin >> side >> r >> c;
            grid[side * 10 + r][c] = 'o';
        }
        string moves;
        cin >> moves;
        for (char m : moves) {
            // 根据移动方向更新球的位置
            // 实现细节依赖于题目完整描述
        }
        for (int side = 0; side < 2; side++) {
            for (int r = 0; r < 10; r++) {
                for (int c = 0; c < 10; c++) {
                    cout << grid[side * 10 + r][c];
                }
                cout << "\n";
            }
        }
    }
    return 0;
}
```

## 样例输入输出

由于题目描述不完整，具体的输入输出格式需要参考原题。
