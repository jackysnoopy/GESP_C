# [PA 2021] Wystawa

## 题目描述
给定长度为 $n$ 的序列 $a, b$。

你需要构造一个序列 $c$，构造方法为：

- 选择 $k$ 个 $i$，令 $c_i \leftarrow a_i$。
- 对于其他 $i$，令 $c_i \leftarrow b_i$。

求序列 $c$ 的最大子段和的最小值，并给出一种方案。

## 输入格式
第一行，两个整数 $n, k$；

第二行，$n$ 个整数 $a_1, a_2, \cdots, a_n$；

第三行，$n$ 个整数 $b_1, b_2, \cdots, b_n$。

## 输出格式
第一行，一个整数，表示序列 $c$ 的最大子段和的最小值；

第二行，一个长为 $n$ 的字符串 $s$，若令 $c_i \leftarrow a_i$，$s_i = \text{A}$；否则，$s_i = \text{B}$。

## 样例
### 样例1
输入:
```
6 2
-1 7 0 2 -5 0
3 1 4 -3 -3 12
```
输出:
```
4
BBABBA
```

### 样例2
输入:
```
3 2
-1 -4 -1
-4 -2 -1
```
输出:
```
0
AAB
```

## 提示
- 时间限制：6000ms
- 内存限制：524288KB

## 解题思路

### 问题分析
需要选择 $k$ 个位置使用 $a_i$，其余使用 $b_i$，使得最大子段和最小。

### 核心思路
1. 二分答案
2. 贪心选择使用 $a_i$ 的位置

### 算法流程
1. 二分最大子段和的最小值
2. 检查是否能通过选择 $k$ 个 $a_i$ 达到
3. 输出方案

### 复杂度分析
- 时间复杂度：$O(n \log R)$
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
    
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    long long low = -1e18, high = 1e18;
    
    while (low < high) {
        long long mid = (low + high) / 2;
        
        int used = 0;
        long long current = 0;
        long long max_current = 0;
        
        for (int i = 0; i < n; i++) {
            long long val = (used < k) ? a[i] : b[i];
            
            current = max(val, current + val);
            max_current = max(max_current, current);
            
            if (max_current > mid) {
                if (used < k) {
                    used++;
                    current = max(a[i], (long long)a[i]);
                    max_current = max(max_current, current);
                }
            }
        }
        
        if (max_current <= mid) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    cout << low << endl;
    
    string s(n, 'B');
    int used = 0;
    
    for (int i = 0; i < n; i++) {
        if (used < k && a[i] > b[i]) {
            s[i] = 'A';
            used++;
        }
    }
    
    cout << s << endl;
    
    return 0;
}
```