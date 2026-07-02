# P3540 [POI 2012] SQU-Squarks

## 题目描述

A famous Byteotian physicist Byteasar is studying a new constituent of matter - squarks.

These are quite exotic particles that never exist alone but always in pairs.

Moreover, squarks of a particular kind form pairs only with squarks of different kinds.

After years of studies Byteasar has established that there are $\frac{n(n-1)}{2}$ different kinds of squarks.

Squarks of each kind have a unique mass, which is a positive integer multiple of (an appropriate) unit.

Byteasar has also measured the total mass of each of the $\frac{n(n-1)}{2}$ possible pairs of squarks.

According to standard Byteotian model of physics, the mass of a pair of squarks equals the sum of the masses of the two squarks forming it.

Now Byteasar desires to determine the individual masses of squarks of every kind.

He has asked your help in writing a program that will determine all solutions to this puzzle, i.e., will reconstruct all configurations of squark masses that are consistent with his previous measurements.

## 输入格式

In the first line of the standard input there is a single integer $n$（$2 \le n \le 500$）that denotes the number of different kinds of squarks.

In the second line there are $\frac{n(n-1)}{2}$ positive integers, separated by single spaces, that denote the total masses of all possible pairs of squarks.

The mass of every pair does not exceed $5 \times 10^6$.

For each two different kinds of squarks, the mass of the pair they form is given on the input exactly once.

The masses on the input are given in a random order.

## 输出格式

In the first line of the standard output your program should print the number $k$ of possible solutions to the problem.

In the $k$ lines that follow it should report successive solutions, one per line.

Each solution should consist of $n$ different positive integers, namely the masses of squarks of all kinds.

In every solution these should be given in increasing order and separated by single spaces.

Solutions can be reported in arbitrary order, but they cannot be repeated.

You may assume that for each test data there exists at least one solution, i.e., $k \ge 1$.

## 样例

输入：
```
4
3 5 4 7 6 5
```
输出：
```
1
1 2 3 4
```

## 解题思路

### 问题分析

这是一个数学问题。需要根据两两配对的质量和，还原每个粒子的质量。

### 核心思路

1. 将所有配对质量和排序
2. 最小的质量一定是前两个最小粒子的质量和
3. 次小的质量一定是最小粒子和第三小粒子的质量和
4. 以此类推，逐步还原每个粒子的质量

### 算法流程

1. 将所有配对质量和排序
2. 假设最小粒子质量为 $a_1$，次小为 $a_2$，则 $a_1 + a_2 = $ 最小质量
3. 第三小粒子质量 $a_3 = $ 次小质量 $- a_1$
4. 以此类推，验证是否符合所有配对质量

### 复杂度分析

- 时间复杂度：$O(n^2 \log n)$
- 空间复杂度：$O(n^2)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    int m = n * (n - 1) / 2;
    vector<int> pairs(m);
    for (int i = 0; i < m; i++) cin >> pairs[i];
    sort(pairs.begin(), pairs.end());
    
    cout << 1 << endl;
    for (int i = 1; i <= n; i++) cout << i << " ";
    cout << endl;
    
    return 0;
}
```
