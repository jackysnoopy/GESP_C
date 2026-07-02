# [USACO17DEC] Greedy Gift Takers P

## 题目描述

Farmer John's nemesis, Farmer Nhoj, has $N$ cows ($1 \leq N \leq 10^5$), conveniently numbered $1 \dots N$. They have unexpectedly turned up at Farmer John's farm, so the unfailingly polite Farmer John is attempting to give them gifts.

To this end, Farmer John has brought out his infinite supply of gifts, and Nhoj's cows have queued up in front of him, with cow $1$ at the head of the queue and cow $N$ at the tail. Farmer John was expecting that at every timestep, the cow at the head of the queue would take a gift from Farmer John and go to the tail of the queue. However, he has just realized that Nhoj's cows are not that polite! After receiving her gift, each cow may not go to the tail of the queue, but rather may cut some number of cows at the tail, and insert herself in front of them. Specifically, cow $i$ will always cut exactly $c_i$ cows ($0 \leq c_i \leq N-1$).


Farmer John knows that some cows might receive multiple gifts; as he has an infinite supply, this does not worry him. But he is worried that some cows might become unhappy if they do not get any gifts.


Help Farmer John find the number of cows who never receive any gifts, no matter how many gifts are handed out.

## 输入格式

The first line contains a single integer, $N$.

The second line contains $N$ space-separated integers $c_1, c_2, \dots, c_N$.

## 输出格式

Please output the number of cows who cannot receive any gifts.

## 样例

### 样例输入 1
```
3
1 2 0
Output:
1
```

### 样例输出 1
```
1
```

## 提示

**数据范围**

{"time": [1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000], "memory": [128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000, 128000]}

## 解题思路

### 问题分析
$N$ 头牛排队，队首牛拿礼物后插到距队尾 $c_i$ 处（即新位置 $N-c_i$）。求无论发多少礼物都拿不到礼物的牛数。

### 核心思路
拿不到礼物的牛构成一个后缀：若牛 $i$ 永远拿不到，它始终挡在 $i+1,\dots,N$ 前面，这些牛也拿不到。设拿不到的牛数为 $x$，则前 $g=N-x$ 头牛能拿到。最后一头能拿到的牛 $g$ 必须能到达队首：其余 $g-1$ 头牛每次拿礼物后落点 $N-c_i$，若 $c_i>x$ 则落在前 $g$ 区域（可能阻挡），否则落到 $g$ 之后（越过牛 $g$，使其前移）。用计数模拟：$c_i>x$ 阻挡数 $+1$，否则抵消一个阻挡；最终无阻挡则牛 $g$ 可达队首。二分最小的可行 $x$。

### 算法流程
1. 二分 $x\in[0,N]$。
2. `check(x)`：$g=N-x$，扫描 $i=1..g-1$，$c_i>x$ 则 `cnt++`，否则 `cnt--`（不为零时）。
3. `cnt==0` 表示牛 $g$ 可拿到礼物，$x$ 可行，找最小可行 $x$。

### 复杂度分析
- 时间复杂度：$O(N\log N)$。
- 空间复杂度：$O(N)$。

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
int N;
vector<int> c;
bool check(int x){
    int g=N-x;
    int cnt=0;
    for(int i=1;i<=g-1;i++){
        if(c[i]>x) cnt++;
        else if(cnt>0) cnt--;
    }
    return cnt==0;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    if(!(cin>>N)) return 0;
    c.assign(N+1,0);
    for(int i=1;i<=N;i++) cin>>c[i];
    int lo=0,hi=N;
    while(lo<hi){
        int mid=(lo+hi)/2;
        if(check(mid)) hi=mid; else lo=mid+1;
    }
    cout<<lo<<"\n";
    return 0;
}
```
