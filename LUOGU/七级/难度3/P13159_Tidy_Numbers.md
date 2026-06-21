# [GCJ 2017 Qualification] Tidy Numbers

## 题目描述

给定一个正整数N，找到小于等于N的最大"整齐数"（tidy number）。
整齐数定义为：从左到右数字非递减。

## 输入格式

每个测试用例一行：正整数N

## 输出格式

输出最大整齐数

## 提示

数据范围：1 ≤ N ≤ 10^18

## 解题思路

### 问题分析
- 给定一个正整数N
- 找到最大且 ≤ N 的"整齐数"
- 整齐数：数字从左到右非递减

### 核心思路
**贪心策略**：
1. 从N开始递减检查
2. 对于每个数字，检查是否为整齐数
3. 找到第一个整齐数即为答案

**优化思路**：
1. 从左到右检查数字
2. 如果发现递减位置，将该位减1，后面全设为9
3. 重复直到数字变整齐

### 算法流程
1. 读入N
2. 从N开始递减检查
3. 检查函数：从左到右数字是否非递减
4. 找到第一个整齐数输出

### 复杂度分析
- 时间复杂度：O(数字位数)，最坏情况需要递减多次
- 空间复杂度：O(数字位数)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;

    // Tidy Numbers：整理数字
    long long ans = n;
    while (true) {
        string s = to_string(ans);
        bool tidy = true;
        for (int i = 1; i < (int)s.length(); i++) {
            if (s[i] > s[i - 1]) {
                tidy = false;
                break;
            }
        }
        
        if (tidy) break;
        ans--;
    }

    cout << ans << "\n";
    return 0;
}
```
