# [USACO25OPEN] OohMoo Milk G

## 题目描述

农夫约翰有 N 个瓶子装牛奶，每天选择 A 个瓶子各加 1 单位牛奶。竞争对手农夫 Nhoj 每天从 B 个非空瓶子各偷 1 单位。经过 D 天后，瓶子含 M 单位牛奶卖出 M^2 moonies。求确定的利润 P。

## 输入格式

第一行 N 和 D。
第二行 A 和 B。
第三行 N 个整数 m_i。

## 输出格式

输出 P 对 10^9+7 取模的结果。

## 样例

### 样例 1
输入：
```
5 4
4 2
4 10 8 10 10
```
输出：
```
546
```

### 样例 2
输入：
```
10 5
5 1
1 2 3 4 5 6 7 8 9 10
```
输出：
```
777
```

## 提示

- 1 ≤ N ≤ 10^5
- 1 ≤ D ≤ 10^9
- 0 ≤ m_i ≤ 10^9

## 解题思路

### 问题分析

这是一个博弈论问题。John 每天加 A 瓶，Nhoj 偷 B 瓶（B < A）。需要找到无论双方如何操作都确定的利润。

### 核心思路

1. 总共增加 D*A 单位牛奶
2. 总共被偷 D*B 单位牛奶
3. 净增加 D*(A-B) 单位
4. 为了让 sum(M^2) 确定，需要均匀分配

### 算法流程

1. 计算每个瓶子的基础增加量
2. 均匀分配净增加量
3. 计算 sum(M^2)

### 复杂度分析

- 时间复杂度：O(N)
- 空间复杂度：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, D, A, B;
    cin >> N >> D >> A >> B;
    
    vector<long long> m(N);
    for (int i = 0; i < N; i++) cin >> m[i];
    
    long long total_added = (long long)D * A;
    long long total_stolen = (long long)D * B;
    
    long long base = total_added / N;
    long long extra = total_added % N;
    
    long long ans = 0;
    for (int i = 0; i < N; i++) {
        long long val = m[i] + base;
        if (i < extra) val++;
        val -= total_stolen / N;
        if (val < 0) val = 0;
        ans = (ans + val % MOD * (val % MOD)) % MOD;
    }
    
    cout << ans << endl;
    return 0;
}
```
