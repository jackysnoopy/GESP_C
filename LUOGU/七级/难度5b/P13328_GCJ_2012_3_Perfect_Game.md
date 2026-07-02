# [GCJ 2012 #3] Perfect Game

## 题目描述

N 个关卡，每个关卡耗时 L[i]，死亡概率 P[i]%。求使连续通关所有关卡的期望时间最小的关卡顺序。

## 输入格式

第一行 T，每组包含 N、数组 L 和数组 P。

## 输出格式

Case #x: 关卡索引排列。

## 样例

```
3
4
1 1 1 1
50 0 20 20
3
100 10 1
0 50 0
3
100 80 50
40 20 80
```

## 解题思路

### 问题分析
每次死亡从第 0 关重新开始。期望时间取决于失败率和耗时的比值。

### 核心思路
排序准则：按 P[i]/L[i] 降序（危险程度/单位时间），比值相同按索引升序。

### 算法流程
1. 对关卡按 P[i]*L[j] > P[j]*L[i] 排序
2. 输出排序后的索引

### 复杂度分析
- 时间：O(N log N)
- 空间：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int t=1; t<=T; t++) {
        int N; cin >> N;
        vector<int> L(N), P(N);
        for (int i=0;i<N;i++) cin>>L[i];
        for (int i=0;i<N;i++) cin>>P[i];
        vector<int> idx(N);
        for (int i=0;i<N;i++) idx[i]=i;
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            long long left = (long long)P[a]*L[b];
            long long right = (long long)P[b]*L[a];
            if (left != right) return left > right;
            return a < b;
        });
        cout << "Case #" << t << ":";
        for (int i=0;i<N;i++) cout<<" "<<idx[i];
        cout << "\n";
    }
    return 0;
}
```
