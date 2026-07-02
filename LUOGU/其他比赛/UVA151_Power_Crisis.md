# UVA151 - Power Crisis (电力危机)

## 题目描述

约瑟夫问题的变种。城市 1..N 按圆形排列。从城市 13 开始，每隔 m 个剩余城市就断开一个。找到最小的 m（m>1）使得城市 13 是最后一个被断开的。输入 N（0 退出）。输出每个 N 对应的 m。N<=100。

## 解题思路

### 问题分析

这是一个约瑟夫问题的变种，需要模拟整个过程来找到满足条件的 m。

### 核心思路

使用模拟法，对每个可能的 m 值进行模拟，直到找到使城市 13 最后被移除的最小 m。

### 算法流程

1. 读取 N
2. 从 m=2 开始尝试
3. 对每个 m，模拟约瑟夫过程
4. 如果城市 13 是最后剩下的，输出 m
5. 否则 m++，继续尝试

### 复杂度分析

- 时间复杂度：O(N^2) 每个 m 需要 O(N) 模拟，最多尝试 O(N) 次
- 空间复杂度：O(N)

## 代码实现

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N && N != 0) {
        for (int m = 2; ; ++m) {
            vector<int> cities(N);
            for (int i = 0; i < N; ++i) cities[i] = i + 1;

            int idx = 0;
            while (cities.size() > 1) {
                idx = (idx + m - 1) % cities.size();
                cities.erase(cities.begin() + idx);
            }
            if (cities[0] == 13) {
                cout << m << "\n";
                break;
            }
        }
    }

    return 0;
}
```
