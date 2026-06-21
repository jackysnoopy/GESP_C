# [USACO03MAR] Best Cow Fences G

## 题目描述
**原题来自：USACO 2003 Mar. Green**

给定一个长度为 $n$ 的非负整数序列 $A$ ，求一个平均数最大的，长度不小于 $L$ 的子段。

## 输入格式
第一行用空格分隔的两个整数 $n$ 和 $L$；

第二行为 $n$ 个用空格隔开的非负整数，表示 $A_i$。

## 输出格式
输出一个整数，表示这个平均数的 $1000$ 倍。不用四舍五入，直接输出。

## 样例
### 样例 1
```
10 6
6 4 2 10 3 8 5 9 4 1
```
```
6500
```

## 提示
$1 \leq n \leq 10^5,0 \leq A_i \leq 2000$。

## 解题思路

### 问题分析
长度为 n 的序列，求长度 ≥ L 的平均数最大的子段。

### 核心思路
二分平均值，检查是否存在长度 ≥ L 的子段平均值 ≥ mid。转化为所有数减去 mid 后，前缀和找最大非负子段和。

### 算法流程
1. 读入 n, L 和序列 A
2. 二分平均值 mid
3. 对每个 mid，将 A[i] 减去 mid 得到 B[i]
4. 求 B 的前缀和，维护 min_pre，找最大和
5. 若最大和 ≥0 则 mid 可行

### 复杂度分析
- 时间复杂度：O(n log C)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int n, L;
vector<int> a;

bool check(double mid) {
    vector<double> pre(n + 1, 0);
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i-1] + a[i-1] - mid;
    double min_pre = 0;
    for (int i = L; i <= n; i++) {
        min_pre = min(min_pre, pre[i - L]);
        if (pre[i] - min_pre >= 0) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> L;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    double lo = 0, hi = 2000;
    for (int iter = 0; iter < 50; iter++) {
        double mid = (lo + hi) / 2;
        if (check(mid)) lo = mid;
        else hi = mid;
    }
    
    cout << (int)(hi * 1000) << "
";
    return 0;
}
```
