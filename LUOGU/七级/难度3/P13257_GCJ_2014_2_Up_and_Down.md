# [GCJ 2014 #2] Up and Down

## 题目描述

You are given a sequence of distinct integers $A = [A_1, A_2, ..., A_N]$, and would like to rearrange it into an up and down sequence (one where $A_1 < A_2 < ... < A_m > A_{m+1} > ... > A_N$ for some index $m$, with $m$ between 1 and $N$ inclusive).

The rearrangement is accomplished by swapping two adjacent elements of the sequence at a time. Predictably, you are particularly interested in the minimum number of such swaps needed to reach an up and down sequence.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing a single integer: $N$. The next line contains $N$ distinct integers: $A_1, ..., A_N$.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the test case number (starting from 1) and $y$ is the minimum number of swaps required to rearrange $A$ into an up and down sequence.

## 样例

### 样例输入 1
```
2
3
1 2 3
5
1 8 10 3 7
```

### 样例输出 1
```
Case #1: 0
Case #2: 1
```

## 提示

**Sample Explanation**

In the first case, the sequence is already in the desired form (with $m=N=3$) so no swaps are required.

In the second case, swapping $3$ and $7$ produces an up and down sequence (with $m=3$).

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq A_i \leq 10^9$.
- The $A_i$ will be pairwise distinct.

**Small dataset(7 Pts)**

- Time limit: ~~60~~ 3 seconds.
- $1 \leq N \leq 10$.

**Large dataset(11 Pts)**

- Time limit: ~~120~~ 5 seconds.
- $1 \leq N \leq 1000$.

## 解题思路

### 问题分析
待补充

### 核心思路
待补充

### 算法流程
待补充

### 复杂度分析
待补充

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