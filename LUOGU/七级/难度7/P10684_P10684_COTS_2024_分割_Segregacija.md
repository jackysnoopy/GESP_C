# P10684 [COTS 2024] 分割 Segregacija

## 题目描述

Pero 有一个 $2$ 行 $N$ 列的矩阵，每个格子里有一个红球或蓝球。

Pero 想要重排矩阵中的球，使得所有蓝球位于矩阵的左上侧，所有红球位于右下侧。

Pero 可以多次交换相邻的两个球。Pero 想知道达到目标所需的最少交换次数。

此外，Pero 会交换矩阵中的相邻两个球 $Q$ 次，并在每次变更后询问当前矩阵状态所需的最小交换次数。

## 输入格式

第一行，两个整数 $N,Q$。
接下来两行，每行一个长度为 $N$ 的字符串，描述这个矩阵。
接下来 $Q$ 行，每行三个正整数 $t,x,y$，描述一次交换操作。

## 输出格式

输出 $(Q+1)$ 行，分别表示初始矩阵的答案和每次修改后的答案。

## 样例

### 样例1
输入：
```
5 2
CPCPC
PCCPC
1 1 4
1 1 2
```
输出：
```
3
4
5
```

## 提示

对于 $100\%$ 的数据，保证 $1\le N\le  10^6$，$0\le Q\le 10^6$。

## 解题思路

### 问题分析

这是一个经典的排序问题。最少交换次数等于逆序对数。

### 核心思路

将矩阵展开成一维序列，计算逆序对数。

### 算法流程

```
将2行N列的矩阵展开成一维序列
计算逆序对数
对于每次交换，更新序列并重新计算
```

### 复杂度分析

- **时间复杂度**：$O(N^2)$（暴力）
- **空间复杂度**：$O(N)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    cin >> N >> Q;
    
    string row1, row2;
    cin >> row1 >> row2;
    
    vector<int> grid(2 * N);
    for (int i = 0; i < N; i++) {
        grid[i] = (row1[i] == 'C') ? 1 : 0;
        grid[N + i] = (row2[i] == 'C') ? 1 : 0;
    }
    
    auto count_inversions = [](vector<int>& g) -> ll {
        ll inv = 0;
        int n = g.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (g[i] > g[j]) inv++;
            }
        }
        return inv;
    };
    
    cout << count_inversions(grid) << "\n";
    
    while (Q--) {
        int t, x, y;
        cin >> t >> x >> y;
        x--; y--;
        
        if (t == 1) {
            swap(grid[x], grid[N + y]);
        } else {
            swap(grid[x], grid[N + y]);
        }
        
        cout << count_inversions(grid) << "\n";
    }
    
    return 0;
}
```
