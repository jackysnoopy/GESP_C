# Dropping Test

## 题目描述

在某个课程中，你需要进行 $n$ 次测试。 

如果你在共计 $b_i$ 道题的测试 $i$ 上的答对题目数量为 $a_i$，你的累积平均成绩就被定义为

$$100	imes \dfrac{\displaystyle \sum_{i=1}^n a_i}{\displaystyle \sum_{i=1}^n b_i}$$

给定您的考试成绩和一个正整数 $k$，如果您被允许放弃任何 $k$ 门考试成绩，您的累积平均成绩的可能最大值是多少。

假设您进行了 $3$ 次测试，成绩分别为 $5/5,0/1$ 和 $2/6$。

在不放弃任何测试成绩的情况下，您的累积平均成绩是

$$100	imes \frac{5+0+2}{5+1+6} \approx 58.33 \approx 58$$

然而，如果你放弃第三门成绩，则您的累积平均成绩就变成了

$$100	imes \frac{5+0}{5+1}\approx 83.33\approx 83$$

## 输入格式

输入包含多组测试用例，每个测试用例包含三行。

对于每组测试用例，第一行包含两个整数 $n$ 和 $k$。

第二行包含 $n$ 个整数，表示所有的 $a_i$。

第三行包含 $n$ 个整数，表示所有的 $b_i$。

当输入用例 $n=k=0$ 时，表示输入终止，且该用例无需处理。

## 输出格式

对于每个测试用例，输出一行结果，表示在放弃 $k$ 门成绩的情况下，可能的累积平均成绩最大值。

结果应四舍五入到最接近的整数。

## 样例

### 样例输入
```
3 1
5 0 2
5 1 6
4 2
1 2 7 9
5 6 7 9
0 0
```

### 样例输出
```
83
100
```

## 提示

数据范围 $1 \le n \le 1000$, $0 \le k < n$, $0 \le a_i \le b_i \le 10^9$。

## 解题思路

### 问题分析

放弃 k 次考试使平均分最大。

### 核心思路

1. 每次考试有 a_i/b_i 的正确率。放弃某些考试使 sum(a)/sum(b) 最大。
2. 二分答案 mid，检查能否通过放弃 k 次使 avg >= mid。
3. 检查方法：计算 c_i = a_i - mid*b_i，放弃最小的 k 个 c_i。

### 算法流程

1. 读入数据
2. 二分答案
3. 每次检查是否可行
4. 输出最大平均分

### 复杂度分析

时间 O(n * log(P) * log(n))

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, k;
    while (cin >> n >> k && (n || k)) {
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];
        double lo = 0, hi = 100;
        for (int iter = 0; iter < 50; ++iter) {
            double mid = (lo + hi) / 2;
            vector<double> c(n);
            for (int i = 0; i < n; ++i) c[i] = a[i] - mid * b[i];
            sort(c.begin(), c.end(), greater<double>());
            double sum = 0;
            for (int i = 0; i < n - k; ++i) sum += c[i];
            if (sum >= 0) lo = mid; else hi = mid;
        }
        printf("%.0f\n", lo * 100);
    }
    return 0;
}
```
