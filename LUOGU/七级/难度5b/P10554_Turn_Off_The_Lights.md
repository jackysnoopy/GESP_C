# Turn Off The Lights

## 题目描述

Kitty 有 $n^2$ 个灯泡，这些灯泡组成了一个 $n\times n$ 的矩阵。

有一天，Kitty 发现这些灯泡中有些是亮的，有些是灭的。Kitty 想要把它们全部关闭。

为了实现她的目标，Kitty 可以执行三种类型的操作：

- (1) 选择一行，反转这一行的状态。这意味着如果这一行的灯泡是亮的，经过此操作后，它将变为灭的。如果这一行的灯泡是灭的，经过此操作后，它将变为亮的。

- (2) 选择一列，反转这一列的状态。这意味着如果这一列的灯泡是亮的，经过此操作后，它将变为灭的。如果这一列的灯泡是灭的，经过此操作后，它将变为亮的。

- (3) 选择一个灯泡，反转这个灯泡的状态。**这种操作最多只能执行 $k$ 次。**

对于当前状态，帮助 Kitty 在 $3n$ 次操作内实现她的目标。

## 输入格式

第一行包含两个整数 $n(1\leq n\leq 1000),k(0\leq k < n)$，如上所述。

接下来有 $n$ 行，每行有正好 $n$ 个数字，$0$ 表示此时灯泡是灭的，而 $1$ 表示相反。

输入中第 $(x+1)$ 行的第 $y$ 个数字表示坐标 $(x,y)$ 处的灯泡。

## 输出格式

如果 Kitty 无法实现她的目标，输出 $-1$ 在一行中。

否则，第一行输出 $M(0\leq M\leq 3n)$，表示她需要执行的操作次数。

接下来的 $M$ 行中，每行包含 $2$ 个整数 $x,y$，用空格分隔。

如果 $1\leq x\leq n,1\leq y\leq n$，表示 Kitty 将反转坐标 $(x,y)$ 处的灯泡。

如果 $x=0,1\leq y\leq n$，表示 Kitty 将反转所有坐标为 $(z,y)1\leq z\leq n$ 的灯泡。

如果 $1\leq x\leq n,y=0$，表示 Kitty 将反转所有坐标为 $(x,z)1\leq z\leq n$ 的灯泡。

如果有多个答案，输出其中任意一个。

## 样例

### 样例1
输入：
```
2 0
0 1
1 0
```
输出：
```
2
0 2
2 0
```

### 样例2
输入：
```
3 1
1 0 0
0 1 0
0 0 1
```
输出：
```
-1
```

## 提示

（由 ChatGPT 4o 翻译）

## 解题思路

### 问题分析

这是一个矩阵翻转问题。我们需要在 $3n$ 次操作内关闭所有灯泡，其中：
- 反转一行或一列是免费的
- 反转单个灯泡最多 $k$ 次

### 核心思路

1. **贪心策略**：从上到下、从左到右处理每个亮着的灯泡
2. **优先使用行列操作**：因为行列操作可以同时影响多个灯泡
3. **单个灯泡操作作为最后手段**：只在必要时使用

### 算法流程

1. 处理前 $n-1$ 行和前 $n-1$ 列：
   - 对于每个亮着的灯泡，反转其所在行
2. 处理最后一列（前 $n-1$ 行）：
   - 对于每个亮着的灯泡，反转其所在行
3. 处理最后一行（前 $n-1$ 列）：
   - 对于每个亮着的灯泡，反转其所在列
4. 处理右下角的灯泡：
   - 如果 $k > 0$，直接反转该灯泡
   - 否则，尝试反转最后一行和最后一列

### 复杂度分析

- 时间复杂度：$O(n^2)$，需要遍历整个矩阵
- 空间复杂度：$O(n^2)$，存储矩阵和操作序列

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    
    // 记录操作
    vector<pair<int, int>> ops;
    
    // 贪心策略：从上到下、从左到右处理
    // 对于每个亮着的灯泡，尝试通过反转行或列来关闭
    
    // 第一遍：处理前n-1行和前n-1列
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (grid[i][j] == 1) {
                // 反转第i行
                ops.push_back({i + 1, 0});
                for (int c = 0; c < n; c++) {
                    grid[i][c] ^= 1;
                }
            }
        }
    }
    
    // 处理最后一列（前n-1行）
    for (int i = 0; i < n - 1; i++) {
        if (grid[i][n - 1] == 1) {
            // 反转第i行
            ops.push_back({i + 1, 0});
            for (int c = 0; c < n; c++) {
                grid[i][c] ^= 1;
            }
        }
    }
    
    // 处理最后一行（前n-1列）
    for (int j = 0; j < n - 1; j++) {
        if (grid[n - 1][j] == 1) {
            // 反转第j列
            ops.push_back({0, j + 1});
            for (int r = 0; r < n; r++) {
                grid[r][j] ^= 1;
            }
        }
    }
    
    // 处理右下角的灯泡
    if (grid[n - 1][n - 1] == 1) {
        // 如果k>0，可以直接反转这个灯泡
        if (k > 0) {
            ops.push_back({n, n});
            grid[n - 1][n - 1] ^= 1;
            k--;
        } else {
            // 尝试其他方案
            // 反转最后一行和最后一列
            ops.push_back({n, 0});
            ops.push_back({0, n});
            for (int c = 0; c < n; c++) {
                grid[n - 1][c] ^= 1;
            }
            for (int r = 0; r < n; r++) {
                grid[r][n - 1] ^= 1;
            }
            // 右下角被翻转了两次，所以还是1
            // 需要再反转一次
            grid[n - 1][n - 1] ^= 1;
        }
    }
    
    // 检查是否全部关闭
    bool allOff = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                allOff = false;
                break;
            }
        }
        if (!allOff) break;
    }
    
    if (!allOff) {
        cout << -1 << endl;
        return 0;
    }
    
    // 输出操作
    cout << ops.size() << endl;
    for (const auto& op : ops) {
        cout << op.first << " " << op.second << endl;
    }
    
    return 0;
}
```
