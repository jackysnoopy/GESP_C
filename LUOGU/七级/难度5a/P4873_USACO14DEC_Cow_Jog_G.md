# [USACO14DEC] Cow Jog G

## 题目描述

Farmer John's $N$ cows $(1 <= N <= 100,000)$ are out exercising their
hooves again, jogging along an infinite track.  Each cow starts at a
distinct position on the track, and some cows run at different speeds.

The track is divided into lanes so that cows may move past each other.
No two cows in the same lane may ever occupy the same position.
Farmer John doesn't want any cow to have to change lanes or adjust
speed, and he wonders how many lanes he will need to accomplish this
if the cows are going to run for $T$ minutes $(1 <= T <= 1,000,000,000).$

## 输入格式

The first line of input contains $N$ and $T$.

The following $N$ lines each contain the initial position and speed of a
single cow.  Position is a nonnegative integer and speed is a positive
integer; both numbers are at most 1 billion.  All cows start at
distinct positions, and these will be given in increasing order in the
input.

## 输出格式

A single integer indicating the minimum number of lanes necessary so
that no two cows in the same lane ever occupy the same location
(including at time $T$).

## 样例

### 样例输入 1
```
5 3
0 1
1 2
2 3
3 2
6 1
Output:
3
```

### 样例输出 1
```
3
```

## 提示

**数据范围**

{"time": [1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000], "memory": [128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000]}

## 解题思路

### 问题分析
$N$ 头牛在无限跑道，初始位置递增、速度各异，跑 $T$ 分钟。同一车道内任意时刻不能有两牛同位置，求最少车道数。

### 核心思路
两牛 $i$（在前位置小）与 $j$（后位置大）冲突当且仅当 $i$ 追上 $j$，即 $e_i\ge e_j$，其中 $e_i=	ext{pos}_i+	ext{speed}_i\cdot T$ 为 $T$ 时刻位置。同一车道内需 $e$ 按起始位置严格递增。最少车道数 = 将序列（按起始位置序）划分为最少严格递增子序列数 = 最长非递增子序列长度（Dilworth）。

### 算法流程
1. 计算 $e_i=	ext{pos}_i+	ext{speed}_i\cdot T$。
2. 求最长非递增子序列长度（用 $-e$ 的最长非递减子序列，`upper_bound` 维护上升数组）。
3. 输出该长度。

### 复杂度分析
- 时间复杂度：$O(N\log N)$。
- 空间复杂度：$O(N)$。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; ll T;
    if(!(cin>>n>>T)) return 0;
    vector<ll> e(n);
    for(int i=0;i<n;i++){ ll p,s; cin>>p>>s; e[i]=p+s*T; }
    // min lanes = length of longest non-increasing subsequence of e
    // = longest non-decreasing subsequence of -e
    vector<ll> d; // ascending
    for(int i=0;i<n;i++){
        ll x=-e[i];
        auto it=upper_bound(d.begin(),d.end(),x);
        if(it==d.end()) d.push_back(x); else *it=x;
    }
    cout<<d.size()<<"\n";
    return 0;
}
```
