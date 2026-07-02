# [USACO22OPEN] Apple Catching G

## 题目描述

天上下苹果了！在某些时刻，一定数量的苹果会落到数轴上。在某些时刻，Farmer John 的一些奶牛将到达数轴并开始接苹果。

如果一个苹果在没有奶牛接住的情况下落到数轴上，它就会永远消失。如果一头奶牛和一个苹果同时到达，奶牛就会接住苹果。每头奶牛每秒可以移动一单位距离。一旦一头奶牛接住了一个苹果，她就会离开数轴。

如果 FJ 的奶牛以最优方式合作，她们总共能接住多少个苹果？

## 输入格式

输入的第一行包含 $N$（$1\le N\le 2\cdot 10^5$），为苹果落到数轴上的次数或 FJ 的奶牛出现的次数。

以下 $N$ 行每行包含四个整数 $q_i$，$t_i$，$x_i$ 和 $n_i$（$q_i\in \{1,2\}, 0\le t_i\le 10^9, 0\le x_i\le 10^9, 1\le n_i\le 10^3$）。

- 如果 $q_i=1$，意味着 FJ 的 $n_i$ 头奶牛在 $t_i$ 时刻来到数轴上的 $x_i$ 位置。
- 如果 $q_i=2$，意味着 $n_i$ 个苹果在 $t_i$ 时刻落到了数轴上的 $x_i$ 位置。

输入保证所有有序对 $(t_i,x_i)$ 各不相同。

## 输出格式

输出 FJ 的奶牛总计能接住的苹果的最大数量。

## 样例

### 样例输入 1
```
5
2 5 10 100
2 6 0 3
2 8 10 7
1 2 4 5
1 4 7 6
Output:
10
```

### 样例输出 1
```
10
```

### 样例输入 2
```
5
2 5 10 100
2 6 0 3
2 8 11 7
1 2 4 5
1 4 7 6
Output:
9
```

### 样例输出 2
```
9
```

## 提示

【样例解释 1】

在这个例子中，在 $t=5$ 时刻落地的 $100$ 个苹果均不能被接住。以下是一种接住 $10$ 个苹果的方式：

- FJ 的所有六头 $t=4$ 时刻到达的奶牛各接一个 $t=8$ 时刻落地的苹果。
- FJ 的一头 $t=2$ 时刻到达的奶牛接一个 $t=8$ 时刻落地的苹果。
- 余下三头 $t=2$ 时刻到达的奶牛各接一个 $t=6$ 时刻落地的苹果。

【样例解释 2】

再一次地，在 $t=5$ 时刻落地的苹果均不能被接住。除此之外，在 $t=2$ 时刻到达的奶牛均不能接住 $t=8$ 时刻落地的苹果。以下是一种接住 $9$ 个苹果的方式：

- FJ 的所有六头 $t=4$ 时刻到达的奶牛各接一个 $t=8$ 时刻落地的苹果。
- 余下三头 $t=2$ 时刻到达的奶牛各接一个 $t=6$ 时刻落地的苹果。

**数据范围**

{"time": [2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000], "memory": [262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144, 262144]}

## 解题思路

### 问题分析
数轴上，奶牛 $t_i$ 时刻到达 $x_i$，苹果 $t_j$ 时刻落到 $x_j$。奶牛每秒移动一单位，可接住到达时刻 $\le t_j$ 且能赶到的苹果（$t_i+|x_i-x_j|\le t_j$）。每牛接一苹果后离开，求最多接住苹果数。

### 核心思路
奶牛 $i$ 能接苹果 $j$ 当且仅当 $t_i-x_i\le t_j-x_j$ 且 $t_i+x_i\le t_j+x_j$（由 $|x_i-x_j|\le t_j-t_i$ 拆分）。化为二维偏序匹配。按 $a=t-x$ 升序扫描，奶牛的 $b=t+x$ 入多重集合；对每个苹果，与池中 $b\le b_a$ 的最大 $b$ 奶牛匹配（贪心保留小 $b$ 奶牛给更紧的苹果），用 `map` 处理多重数。

### 算法流程
1. 每事件算 $a=t-x$、$b=t+x$，按 $a$ 升序（同 $a$ 奶牛先于苹果）。
2. 奶牛：`pool[b]+=cnt`；苹果：循环取 `pool` 中最大 $\le b_a$ 的 $b$，批量匹配 $\min(need,cnt)$，耗尽则删除。
3. 累加匹配数输出。

### 复杂度分析
- 时间复杂度：$O(N\log N)$。
- 空间复杂度：$O(N)$。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N; if(!(cin>>N)) return 0;
    struct Ev{ ll a,b; int type; ll cnt; };
    vector<Ev> evs;
    for(int i=0;i<N;i++){
        int q; ll t,x,n; cin>>q>>t>>x>>n;
        ll a=t-x, b=t+x;
        evs.push_back({a,b,q,n}); // q:1 cow, q:2 apple
    }
    sort(evs.begin(),evs.end(),[](const Ev&p,const Ev&q){
        if(p.a!=q.a) return p.a<q.a;
        return p.type<q.type; // cows(type1) before apples(type2) at same a
    });
    map<ll,ll> pool; // cow b -> count
    ll ans=0;
    for(auto&e:evs){
        if(e.type==1){ pool[e.b]+=e.cnt; }
        else{
            ll need=e.cnt;
            while(need>0 && !pool.empty()){
                auto it=pool.upper_bound(e.b);
                if(it==pool.begin()) break;
                --it;
                ll take=min(need, it->second);
                ans+=take; need-=take; it->second-=take;
                if(it->second==0) pool.erase(it);
            }
        }
    }
    cout<<ans<<"\n";
    return 0;
}
```
