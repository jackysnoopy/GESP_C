# [ICPC 2016 WF] Swap Space

## 题目描述

You administer a large cluster of computers with hard drives that use various file system types to store data. You recently decided to unify the file systems to the same type. That is quite a challenge since all the drives are currently in use, all of them are filled with important data to the limits of their capacities, and you cannot afford to lose any of the data. Moreover, reformatting a drive to use a new file system may significantly change the drive’s capacity. To make the reformat possible, you will have to buy an extra hard drive. Obviously, you want to save money by minimizing the size of such extra storage.

You can reformat the drives in any order. Prior to reformatting a drive, you must move all data from that drive to one or more other drives, splitting the data if necessary. After a drive is reformatted, you can immediately start using it to store data from other drives. It is not necessary to put all the data on the same drives they originally started on – in fact, this might even be impossible if some of the drives have smaller capacity with the new file system. It is also allowed for some data to end up on the extra drive.

As an example, suppose you have four drives $A$, $B$, $C$, and $D$ with drive capacities $6$, $1$, $3$, and $3$ GB. Under the new file system, the capacities become $6$, $7$, $5$, and $5$ GB, respectively. If you buy only $1$ GB of extra space, you can move the data from drive $B$ there and then reformat drive $B$. Now you have $7$ GB free on drive $B$, so you can move the $6$ GB from drive $A$ there and reformat drive $A$. Finally, you move the six total gigabytes from drives $C$ and $D$ to drive $A$, and reformat $C$ and $D$.

## 输入格式

The input begins with a line containing one integer $n$ ($1 \le n \le 10^6$), which is the number of drives in your cluster. Following this are $n$ lines, each describing a drive as two integers $a$ and $b$, where $a$ is the capacity with the old file system and $b$ is the capacity with the new file system.

All capacities are given in gigabytes and satisfy $1 \le a,b \le 10^9$. (One thousand petabytes should be enough for everyone, right?)

## 输出格式

Display the total extra capacity in gigabytes you must buy to reformat the drives.

## 样例

### 样例输入 1
```
4
6 6
1 7
3 5
3 5

Output:
1
```

### 样例输出 1
```
1
```

### 样例输入 2
```
4
2 2
3 3
5 1
5 10

Output:
5
```

### 样例输出 2
```
5
```

## 提示

Time limit: 5000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016

**数据范围**

{"time": [5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000], "memory": [1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576, 1048576]}

## 解题思路

### 问题分析
$n$ 块硬盘，旧容量 $a_i$、新容量 $b_i$，重排前需把数据移到别处。求最小额外存储使所有盘能依次重排。

### 核心思路
分两组：扩容盘（$b_i\ge a_i$）按 $a_i$ 升序先处理（先重排需求小的，逐步积累空闲）；缩容盘（$b_i<a_i$）按 $b_i$ 降序后处理（先留下较多空闲给后续）。模拟过程中所需初始空闲 $=\max(a_i-	ext{当前空闲})$ 的最大值即为答案。

### 算法流程
1. 扩容盘按 $a$ 升序，缩容盘按 $b$ 降序。
2. 维护 `free`（相对额外存储的空闲）与 `req`（所需额外存储）。
3. 每块盘：`req=max(req,a_i-free)`，再 `free+=b_i-a_i`。
4. 输出 `req`。

### 复杂度分析
- 时间复杂度：$O(n\log n)$。
- 空间复杂度：$O(n)$。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<pair<ll,ll>> grow,shr;
    for(int i=0;i<n;i++){ll a,b;cin>>a>>b; if(b>=a)grow.push_back({a,b}); else shr.push_back({a,b});}
    sort(grow.begin(),grow.end());
    sort(shr.begin(),shr.end(),[](const pair<ll,ll>&x,const pair<ll,ll>&y){return x.second>y.second;});
    ll req=0,free=0;
    for(auto&e:grow){ req=max(req,e.first-free); free+=e.second-e.first; }
    for(auto&e:shr){ req=max(req,e.first-free); free+=e.second-e.first; }
    cout<<req<<"\n";
    return 0;
}
```
