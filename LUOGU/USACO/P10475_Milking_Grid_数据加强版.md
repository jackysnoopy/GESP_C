# [USACO03FALL] Milking Grid（数据加强版）

## 题目描述
Every morning when they are milked, the Farmer John's cows form a rectangular grid that is $R (1 \leq R \leq 10,000)$ rows by $C (1 \leq C \leq 75)$ columns. As we all know, Farmer John is quite the expert on cow behavior, and is currently writing a book about feeding behavior in cows. He notices that if each cow is labeled with an uppercase letter indicating its breed, the two-dimensional pattern formed by his cows during milking sometimes seems to be made from smaller repeating rectangular patterns.

Help FJ find the rectangular unit of smallest area that can be repetitively tiled to make up the entire milking grid. Note that the dimensions of the small rectangular unit do not necessarily need to divide evenly the dimensions of the entire milking grid, as indicated in the sample input below.

## 输入格式
- Line $1$: Two space-separated integers: $R$ and $C$

- Lines $2\dots R+1$: The grid that the cows form, with an uppercase letter denoting each cow's breed. Each of the $R$ input lines has $C$ characters with no space or other intervening character.

## 输出格式
- Line 1: The area of the smallest unit from which the grid is formed

## 样例
### 样例 1
```
2 5 
ABABA 
ABABA

```
```
2
```

## 提示
The entire milking grid can be constructed from repetitions of the pattern `AB`.

## 解题思路
### 问题分析
R×C 字符矩阵，求最小的子矩阵使其重复铺满整个矩阵。

### 核心思路
分别求行和列的最小周期覆盖。对每行看作一个整体求行最小周期，对每列求列最小周期。

### 算法流程
1. 读入 R, C 和矩阵
2. 将每行字符串哈希，对行哈希序列求最小周期
3. 将每列字符串哈希，对列哈希序列求最小周期
4. 面积 = 行周期 × 列周期

### 复杂度分析
- 时间复杂度：O(RC)
- 空间复杂度：O(RC)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef unsigned long long ULL;
const ULL P = 131;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int R, C; cin >> R >> C;
    vector<string> mat(R);
    for (int i = 0; i < R; i++) cin >> mat[i];
    
    // 行哈希
    vector<ULL> row_hash(R, 0);
    for (int i = 0; i < R; i++)
        for (char c : mat[i])
            row_hash[i] = row_hash[i] * P + c;
    
    // 列哈希
    vector<ULL> col_hash(C, 0);
    for (int j = 0; j < C; j++)
        for (int i = 0; i < R; i++)
            col_hash[j] = col_hash[j] * P + mat[i][j];
    
    // 找行最小周期
    auto min_period = [](const vector<ULL>& a) {
        int n = a.size();
        for (int p = 1; p <= n; p++) {
            if (n % p != 0) continue;
            bool ok = true;
            for (int i = p; i < n && ok; i++)
                if (a[i] != a[i % p]) ok = false;
            if (ok) return p;
        }
        return n;
    };
    
    int rp = min_period(row_hash);
    int cp = min_period(col_hash);
    
    cout << rp * cp << "\n";
    return 0;
}
```
