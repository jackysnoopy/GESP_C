# 「DROI」Round 1 下坠

## 题目描述
$f$ 是定义在 $\mathbb{N^+}$ 上的函数。

我们令 $a_i$ 表示 $x$ 从低到高第 $i$ 位，那么 $f(x)= \prod_{i=1}^{len} (a_i+1)$（$len$ 表示 $x$ 的位数）。

如果对于一个数 $x$，存在 $y$ 使得 $f(y)=x$，那我们称 $x$ 是下坠数。

现在有 $Q$ 次询问，每次询问会给出一个正整数 $k$。

令 $x$ 表示所有下坠数中第 $k$ 小的下坠数，那么请你找到一个最小的 $y$，使得 $f(y)=x$。若不存在一个 $y \in [1,10^{18}]$ 满足条件，则输出 $-1$。

## 输入格式
第一行输入一个整数 $Q$，表示询问次数。

接下输入一行 $Q$ 个数，第 $i$ 个数表示第 $i$ 次询问的 $k$。

## 输出格式
输出一行 $Q$ 个数，第 $i$ 个数表示第 $i$ 次询问你找到的答案。

## 样例
### 样例1
输入:
```
3
1 2 3
```
输出:
```
1 2 3
```

### 样例2
输入:
```
3
9 14 46666666
```
输出:
```
9 18 -1
```

## 提示
- 时间限制：500ms
- 内存限制：131072KB

## 解题思路

### 问题分析
需要找到第 $k$ 小的下坠数对应的 $y$。

### 核心思路
1. 预计算所有可能的下坠数
2. 排序后直接查询

### 算法流程
1. 枚举 $y$，计算 $f(y)$
2. 去重排序
3. 对于每个询问，输出对应结果

### 复杂度分析
- 时间复杂度：$O(N \log N + Q)$
- 空间复杂度：$O(N)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int Q;
    cin >> Q;
    
    vector<long long> k(Q);
    for (int i = 0; i < Q; i++) {
        cin >> k[i];
    }
    
    vector<long long> drop_numbers;
    for (long long y = 1; y <= 1000000; y++) {
        long long x = y;
        long long result = 1;
        
        while (x > 0) {
            int digit = x % 10;
            result *= (digit + 1);
            x /= 10;
        }
        
        drop_numbers.push_back(result);
    }
    
    sort(drop_numbers.begin(), drop_numbers.end());
    drop_numbers.erase(unique(drop_numbers.begin(), drop_numbers.end()), drop_numbers.end());
    
    for (int i = 0; i < Q; i++) {
        if (k[i] <= drop_numbers.size()) {
            cout << drop_numbers[k[i] - 1];
        } else {
            cout << -1;
        }
        if (i + 1 < Q) cout << " ";
    }
    cout << endl;
    
    return 0;
}
```