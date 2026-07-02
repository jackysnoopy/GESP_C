# UVA108 - Maximum Subarray

## 题目描述

给定一个 n×n 的整数矩阵，找出一个子矩形（连续子数组），使得该子矩形内所有元素的和最大。

## 输入格式

- 第一行：整数 n (1 ≤ n ≤ 100)，表示矩阵的大小
- 接下来 n 行，每行 n 个整数，表示矩阵的元素

## 输出格式

输出一个整数，表示最大子矩形的元素和。

## 样例输入

```
4
0 -2 -7 0
9 2 -6 2
-4 1 -4 1
-1 8 0 -2
```

## 样例输出

```
15
```

样例中，最大子矩形为：
```
9 2
-4 1
-1 8
```
其和为 9+2+(-4)+1+(-1)+8 = 15。

## 解题思路

这是一个二维最大子数组问题，可以转化为一维问题来解决。

### 核心思想

1. **枚举列边界**：对于每一对列边界 (left, right)，我们确定子矩形的左右边界。

2. **行压缩**：对于固定的列边界，将每一行在 [left, right] 范围内的元素求和，得到一个一维数组 rowSum。

3. **Kadane算法**：对压缩后的一维数组应用 Kadane 算法，求出最大子数组和。

4. **全局最优**：遍历所有列边界组合，取最大值。

### 算法步骤

```
1. 预处理前缀和，方便快速计算行区间和
2. 枚举所有列边界组合 (left, right)
3. 对于每个组合：
   - 计算每行在 [left, right] 的和
   - 用 Kadane 算法求最大子数组和
4. 更新全局最大值
```

### Kadane 算法

Kadane 算法用于在一维数组中找到最大子数组和：

```
currentSum = max(arr[i], currentSum + arr[i])
bestSum = max(bestSum, currentSum)
```

- 如果 currentSum < 0，则从当前元素重新开始
- 否则，将当前元素加入现有子数组

## 复杂度分析

- **时间复杂度**：O(n³)
  - 枚举列边界：O(n²)
  - 对每个列边界组合计算行和：O(n)
  - Kadane 算法：O(n)
  - 总计：O(n² × n) = O(n³)

- **空间复杂度**：O(n²)
  - 存储矩阵：O(n²)
  - 前缀和数组：O(n²)
  - 临时数组 rowSum：O(n)

## 代码说明

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // 读入矩阵
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    
    // 前缀和：计算每行的前缀和
    vector<vector<int>> prefix(n, vector<int>(n + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            prefix[i][j + 1] = prefix[i][j] + matrix[i][j];
        }
    }
    
    int maxSum = -1000000000;  // 初始化为极小值
    
    // 枚举左右边界
    for (int left = 0; left < n; left++) {
        for (int right = left; right < n; right++) {
            // 计算每行在[left, right]范围内的和
            vector<int> rowSum(n, 0);
            for (int i = 0; i < n; i++) {
                rowSum[i] = prefix[i][right + 1] - prefix[i][left];
            }
            
            // Kadane算法求最大子数组和
            int currentSum = 0;
            int bestSum = -1000000000;
            for (int i = 0; i < n; i++) {
                currentSum = max(rowSum[i], currentSum + rowSum[i]);
                bestSum = max(bestSum, currentSum);
            }
            
            maxSum = max(maxSum, bestSum);
        }
    }
    
    cout << maxSum << endl;
    
    return 0;
}
```

## 测试用例

| 输入 | 输出 | 说明 |
|------|------|------|
| 4<br>0 -2 -7 0<br>9 2 -6 2<br>-4 1 -4 1<br>-1 8 0 -2 | 15 | 样例 |
| 1<br>-1 | -1 | 全负数 |
| 2<br>1 2<br>3 4 | 10 | 全正数 |
| 3<br>-1 -2 -3<br>-4 -5 -6<br>-7 -8 -9 | -1 | 全负数 |
