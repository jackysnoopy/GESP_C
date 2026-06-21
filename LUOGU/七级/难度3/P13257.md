# [GCJ 2014 #2] Up and Down

## 题目描述

给定 $N$ 个互不相同的整数 $A_1,\dots,A_N$，每次交换两个相邻元素，求把它重排成“先严格递增再严格递减”的峰形序列（即存在 $m$ 使 $A_1<\cdots<A_m>\cdots>A_N$）所需的最少相邻交换次数。

## 输入格式

第一行 $T$。每组第一行 $N$，第二行 $N$ 个互不相同的整数 $A_i$。

## 输出格式

每组输出 `Case #x: y`，$y$ 为最少交换次数。

## 提示

- $1\le T\le100$，$1\le N\le1000$，$1\le A_i\le10^9$，$A_i$ 两两不同。
- 样例 1：`1 2 3` 已是峰形（$m=N=3$），交换 0 次。
- 样例 2：`1 8 10 3 7` 交换 3 和 7 得 `1 8 10 7 3`（$m=3$），交换 1 次。

## 解题思路

### 问题分析

相邻交换的最少次数等于“原排列到目标排列的逆序对数”。我们需要选择一个目标峰形排列使逆序对数最小。峰形序列的关键性质：从两端向中间看，数值严格递增。因此最小的数必在某一端，去掉它后次小的数在剩余序列的某一端……即第 $k$ 小的数总落在当前剩余区间的左端或右端。

### 核心思路

按数值从小到大依次放置每个数，每次决定放在“左侧递增段”还是“右侧递减段”。放在左端时，该数要越过它左边所有“尚未放置（即比它大）的数”；放在右端时同理越过右边所有尚未放置的数。这部分越过的数量就是该数贡献的逆序对数。

设当前放置第 $i$ 小的数（0 基），其原始下标为 $p$。已放置（更小）的数有 $i$ 个。用树状数组维护已放置数的下标，则：

- 左侧尚未放置数 = $p - (\text{已放置且下标}<p\text{ 的个数})$；
- 右侧尚未放置数 = $(N-i-1) - \text{左侧尚未放置数}$。

设 `dp[j]` 表示已处理若干最小的数、其中 $j$ 个放在左侧时的最小代价。放左侧转移到 `dp[j+1]`（代价加左侧未放置数），放右侧转移到 `dp[j]`（代价加右侧未放置数）。

### 算法流程

1. 将 $A$ 按值升序排序，记录各值原始下标。
2. 初始化 `dp[0]=0`，其余为 INF；树状数组清零。
3. 依次处理第 $i$ 小的数（下标 $p$）：用树状数组求 `placed_left = sum(p-1)`，算出 `unplaced_left / unplaced_right`；对每个 $j$ 做两种转移得到 `ndp`；交换数组后把 $p$ 加入树状数组。
4. 答案为最终 `dp[j]` 的最小值。

### 复杂度分析

DP 状态 $O(N^2)$，每个数树状数组查询 $O(\log N)$，总时间 $O(N^2)$，空间 $O(N)$。$N\le1000$ 时约 $10^6$，绰绰有余。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct BIT {
    int n;
    vector<int> t;
    BIT(int n=0):n(n),t(n+1,0){}
    void add(int i,int v){ for(++i; i<=n; i+=i&(-i)) t[i]+=v; }
    int sum(int i){ int s=0; for(++i; i>0; i-=i&(-i)) s+=t[i]; return s; }
};

int main(){
    int T; cin >> T;
    for(int tc=1; tc<=T; ++tc){
        int N; cin >> N;
        vector<long long> A(N);
        for(int i=0;i<N;++i) cin >> A[i];
        vector<pair<long long,int>> v(N);
        for(int i=0;i<N;++i) v[i] = {A[i], i};
        sort(v.begin(), v.end());           // increasing value

        BIT bit(N);
        const long long INF = LLONG_MAX/4;
        vector<long long> dp(N+1, INF), ndp(N+1, INF);
        dp[0] = 0;
        for(int i=0;i<N;++i){
            int p = v[i].second;            // original index of i-th smallest
            int placed_left = (p==0) ? 0 : bit.sum(p-1);
            long long unplaced_total = N - i;          // including current
            long long unplaced_left  = (long long)p - placed_left;
            long long unplaced_right = (unplaced_total - 1) - unplaced_left;
            for(int j=0;j<=N;++j) ndp[j] = INF;
            for(int j=0;j<=i;++j){
                if(dp[j] >= INF) continue;
                // place on the increasing (left) side
                if(dp[j] + unplaced_left < ndp[j+1]) ndp[j+1] = dp[j] + unplaced_left;
                // place on the decreasing (right) side
                if(dp[j] + unplaced_right < ndp[j]) ndp[j] = dp[j] + unplaced_right;
            }
            swap(dp, ndp);
            bit.add(p, 1);
        }
        long long ans = *min_element(dp.begin(), dp.end());
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
```
