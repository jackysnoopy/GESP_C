# [BalticOI 2015] Network

## 题目描述

The government of Byteland has decided that it is time to connect their little country to the Internet, so that all citizens can participate in programming competitions and watch videos of cute cats. When it was time to build the network backbone of the country, they assigned the company Internet Optimists Inc. with connecting all the $N$ computers of Byteland. The connections were made as direct links between pairs of computers in such a way that any pair of computers are connected by a sequence of links.

Byteland is not a rich country by any means, so to minimize costs the network topology was built in the form of a tree (i.e. there are exactly $N-1$ direct links between computers). Far too late, it was realised that this solution suffers from a serious drawback. If just a single link is broken, the computers of Byteland will be partitioned so that some computers cannot communicate with each other! To improve the reliability of Byteland's network, it was decided that it should at least tolerate if a single link is broken. Your task is to help Internet Optimists Inc. to improve the network in a cheapest way. Given the network topology of Byteland (i.e. which $N-1$ pairs of computers are connected by direct links), find the minimum number of links that need to be added so that the network will still be connected if any single link is broken.

## 输入格式

The first line of input contains a positive integer $N$ ( $N \geq 3$ ) , the number of computers in Byteland. For simplicity, all computers are numbered from $1$ to $N$. Each of the following $N-1$ lines contains a pair of integers $a$ and $b$ ( $1\leq a,b \leq n,a \ne b$ ) that describes a direct link between computers $a$ and $b$.

## 输出格式

In the first line of output your program should write an integer $k$, the minimal number of links that should be added to the network. In each of the following $k$ lines your program should write a pair of integers $a$ and $b$ ( $1\leq a,b \leq n,a \ne b$ ) that denote the numbers of computers that should be connected by a link. The links can be written in any order. If there is more than one solution, your program should output any one of them.

## 样例

### 样例输入 1
```
6
1 2
2 3
2 4
5 4
6 4
Output:
2
1 5
3 6
```

### 样例输出 1
```
2
1 5
3 6
```

## 提示

$3 \le N \le 500000$

**数据范围**

{"time": [1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000], "memory": [512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000, 512000]}

## 解题思路

### 问题分析
一棵 $N$ 节点的树（网络），添加最少的边使其变为 2-边连通（任意删一条边仍连通）。

### 核心思路
树中"桥"即所有边。要消除桥，须为每条树边提供一条备用路径。叶子（度 1 节点）是关键：每个叶子的入边是桥，必须有一条新边从该叶子所在子树连出。最优做法是将叶子两两配对连边：连接叶子 $a,b$ 后，$a$ 到 $b$ 路径上所有边都获得一条备用路径（成环）。因此最少新增边数 $=\lceil L/2
ceil$（$L$ 为叶子数），将叶子按顺序前后配对（$i$ 与 $i+\lfloor L/2
floor$）即可覆盖所有"桥边"。

### 算法流程
1. 读入树，统计度数为 1 的叶子节点（共 $L$ 个）。
2. 输出 $\lceil L/2
ceil$。
3. 配对：$i$ 与 $i+\lfloor L/2
floor$（$0\le i<\lfloor L/2
floor$）；若 $L$ 为奇数，额外连 $leaves[0]$ 与 $leaves[\lfloor L/2
floor]$。

### 复杂度分析
- 时间复杂度：$O(N)$。
- 空间复杂度：$O(N)$。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n;
vector<vector<int>> g;
vector<int> leaves;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    if(!(cin>>n)) return 0;
    g.assign(n+1,{});
    for(int i=0;i<n-1;i++){int a,b;cin>>a>>b;g[a].push_back(b);g[b].push_back(a);}
    if(n==2){ cout<<1<<"\n"<<1<<" "<<2<<"\n"; return 0; }
    for(int i=1;i<=n;i++) if((int)g[i].size()==1) leaves.push_back(i);
    int L=leaves.size();
    cout<<(L+1)/2<<"\n";
    for(int i=0;i<L/2;i++) cout<<leaves[i]<<" "<<leaves[i+L/2]<<"\n";
    if(L&1) cout<<leaves[0]<<" "<<leaves[L-1]<<"\n";
    return 0;
}
```
