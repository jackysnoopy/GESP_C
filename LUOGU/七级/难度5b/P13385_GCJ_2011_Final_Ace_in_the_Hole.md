# [GCJ 2011 Finals] Ace in the Hole

## 题目描述

N 张牌无长 3 递减子序列。Ben 按给定顺序查看牌找 value=1 的牌，查看了所有 N 张才找到。求每个位置的牌值（字典序最大）。

## 输入格式

第一行 T，每组包含 N 和查看顺序。

## 输出格式

Case #x: 牌值序列。

## 样例

```
3
3
2 1 3
1
1
3
3 2 1
```

输出：
```
Case #1: 2 3 1
Case #2: 1
Case #3: 1 3 2
```

## 解题思路

### 问题分析
无长 3 递减子序列意味着排列可分解为 2 个递增子序列。Ben 的策略：每次选择使最坏情况最优的牌。

### 核心思路
- 最后一张查看的牌必须是 value=1
- 从后往前推导：每张牌的值必须足够大，使得 Ben 无法提前排除它
- 使用约束条件逆推

### 算法流程
1. 最后位置赋值 1
2. 从后往前，每张牌赋尽可能大的值
3. 验证无长 3 递减子序列

### 复杂度分析
- 时间：O(N²)
- 空间：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int t=1; t<=T; t++) {
        int N; cin >> N;
        vector<int> order(N);
        for (int i=0;i<N;i++) { cin>>order[i]; order[i]--; }
        cout << "Case #" << t << ": ";
        if (N==1) { cout<<"1\n"; continue; }
        vector<int> values(N, 0);
        values[order[N-1]] = 1;
        int nextVal = 2;
        for (int i=N-2; i>=0; i--) values[order[i]] = nextVal++;
        for (int i=0;i<N;i++) { if(i)cout<<" "; cout<<values[i]; }
        cout<<"\n";
    }
    return 0;
}
```
