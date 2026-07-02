# [GCJ 2012 Finals] Upstairs/Downstairs

## 题目描述

Konstantin 做活动，每个活动使 Ilia 醒来概率为 a/b。求做至少 K 个活动时 Ilia 被吵醒（从睡到醒）的最小概率。

## 输入格式

第一行 T，每组包含 N、K 和 N 行 "a/b c"。

## 输出格式

Case #x: Q（概率，误差 ≤1e-6）。

## 样例

```
3
4 1
1/2 3
1/5 2
2/5 1
2/2 2
...
```

## 解题思路

### 问题分析
Ilia 初始醒着。如果 Ilia 在某次活动后睡着（概率 1-p），下一次活动后醒（概率 p），则发生"吵醒"。Q = P(至少发生一次吵醒)。

### 核心思路
- 安全策略：先做 p=0 的活动（不会改变状态）
- 然后按 p 升序做其他活动
- 用概率 DP 或直接计算 Q

### 算法流程
1. 安全活动先做（p=0，不触发状态变化）
2. 按 p 升序排列
3. 计算吵醒概率

### 复杂度分析
- 时间：O(N log N + K)
- 空间：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int t=1; t<=T; t++) {
        int N, K; cin >> N >> K;
        vector<double> p(N); vector<int> c(N);
        for (int i=0;i<N;i++) {
            int a,b; char s; cin>>a>>s>>b>>c[i];
            p[i]=(double)a/b;
        }
        vector<int> order(N);
        for (int i=0;i<N;i++) order[i]=i;
        sort(order.begin(), order.end(), [&](int a, int b){return p[a]<p[b];});
        double Q = 0.0; int rem = K;
        for (int i=0;i<N && rem>0;i++) {
            int idx = order[i];
            int use = min(rem, c[idx]);
            for (int j=0;j<use;j++) {
                if (j==0 && i==0) { rem-=use; break; }
                if (p[idx]>0) Q += (1.0-Q)*p[idx];
            }
            rem -= use;
        }
        printf("Case #%d: %.9f\n", t, Q);
    }
    return 0;
}
```
