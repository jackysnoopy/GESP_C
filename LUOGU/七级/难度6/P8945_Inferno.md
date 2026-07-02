# Inferno

## 题目描述
下面有一行由 $1,-1$ 组成的长度为 $n$ 的序列。面具经受了岁月的侵蚀，序列中有一些数已经模糊不清。

你只得往空缺的位置填 $k$ 个 $1$，其余填入 $-1$，需要最大化这个序列的最大子段和。

## 输入格式
第一行两个正整数 $n,k$。

接下来一行 $n$ 个整数 $a_i\in\{-1,0,1\}$，其中 $0$ 表示数字模糊不清。

## 输出格式
一行一个正整数，表示可能的最大子段和。

## 样例
### 样例1
输入:
```
3 2
1 0 0
```
输出:
```
2
```

## 提示
- 时间限制：1000ms
- 内存限制：131072KB

## 解题思路

### 问题分析
需要在 $0$ 的位置填入 $1$ 或 $-1$，使得最大子段和最大。

### 核心思路
1. 优先在能增加子段和的位置填入 $1$
2. 使用贪心策略选择填入位置

### 算法流程
1. 统计 $0$ 的位置
2. 尝试在每个 $0$ 的位置填入 $1$
3. 计算最大子段和

### 复杂度分析
- 时间复杂度：$O(n)$
- 空间复杂度：$O(n)$

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
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int zeros = 0;
    for (int x : a) {
        if (x == 0) zeros++;
    }
    
    int filled = min(k, zeros);
    
    long long max_sum = 0;
    long long current = 0;
    
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            if (filled > 0) {
                current += 1;
                filled--;
            } else {
                current += -1;
            }
        } else if (a[i] == 1) {
            current += 1;
        } else {
            current += -1;
        }
        
        max_sum = max(max_sum, current);
        if (current < 0) current = 0;
    }
    
    cout << max_sum << endl;
    
    return 0;
}
```