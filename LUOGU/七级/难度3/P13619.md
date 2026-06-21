# [ICPC 2024 APC] Duplicates

## 题目描述

给定一个 $n \times n$ 的矩阵 $X$，每个元素是 $1$ 到 $n$ 之间的整数。你可以把若干元素修改为 $1$ 到 $n$ 之间的任意整数，要求修改后：

- 每一行都**含有重复元素**（即存在某个值出现至少两次）；
- 每一列都**含有重复元素**。

求最少修改次数，并给出一种方案。

## 输入格式

第一行一个整数 $t$ 表示测试组数。每组第一行 $n$（$3\le n\le 100$），随后 $n$ 行每行 $n$ 个整数。所有测试组 $n^2$ 之和不超过 $10^4$。

## 输出格式

每组第一行输出最少修改次数 $m$，随后 $m$ 行每行三个整数 $i,j,v$ 表示把 $X_{ij}$ 改成 $v$。

## 提示

样例 1 修改后的矩阵每行每列均含重复元素，且修改次数 2 为最小值。

## 解题思路

### 问题分析

关键观察：一行有 $n$ 个取值在 $[1,n]$ 的数。它**不含重复元素**当且仅当这 $n$ 个数两两不同，即它恰好是 $\{1,\dots,n\}$ 的一个排列。因此：

- 一行是"坏行"（需要修复）当且仅当它是 $1..n$ 的排列；
- 一列是"坏列"当且仅当它是 $1..n$ 的排列。

修改一个格 $(i,j)$ 只会影响第 $i$ 行和第 $j$ 列。把排列中的某个元素改成不同值，必然在该行/该列制造出一个重复。所以一次修改至多修复一条坏行和一条坏列。

### 核心思路

设坏行数为 $a$、坏列为 $b$。每次修改只在某一行内，至多修复一条坏行，故修改次数 $\ge a$；同理 $\ge b$，因此下界为 $\max(a,b)$。

下面构造达到 $\max(a,b)$ 的方案：

1. **配对**：把 $\min(a,b)$ 条坏行与 $\min(a,b)$ 条坏列一一配对，在交点 $(r_k,c_k)$ 修改。该行该列原本都是排列，把 $X_{r_kc_k}$ 改成任意不同值即可同时让两者产生重复，且不影响其它行列。
2. **多余的坏行**（$a>b$ 时）：对每条剩余坏行，选一条**好列**修改一个格。选择新值 $w$ 为该列中某个与原值不同的已有值（若整列同值则取 $v\bmod n+1$），这样行获得重复、列保持有重复。
3. **多余的坏列**（$b>a$ 时）：对称处理，在好行上修改。

由于每条行/每条列至多被修改一次，各修改互不干扰，最终所有行列都含重复元素，且总数恰为 $\max(a,b)$。

### 算法流程

1. 对每行/每列判断是否为排列，统计坏行集合 $R$、坏列集合 $C$。
2. $m=\max(|R|,|C|)$。
3. 配对修改交点；剩余坏行用未使用的**好列**修复，剩余坏列用未使用的**好行**修复。
4. 输出 $m$ 与各次修改。

### 复杂度分析

判断每行每列 $O(n^2)$，构造 $O(n)$。总计 $O(n^2)$ 每组，满足 $\sum n^2\le 10^4$。

## 参考代码
```cpp
#include <cstdio>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        vector<vector<int>> X(n, vector<int>(n));
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%d", &X[i][j]);
        vector<int> badRows, badCols;
        vector<char> rowBad(n,0), colBad(n,0);
        for(int i=0;i<n;i++){
            vector<char> seen(n+1,0);
            bool perm = true;
            for(int j=0;j<n;j++){
                if(seen[X[i][j]]){ perm=false; break; }
                seen[X[i][j]]=1;
            }
            if(perm){ badRows.push_back(i); rowBad[i]=1; }
        }
        for(int j=0;j<n;j++){
            vector<char> seen(n+1,0);
            bool perm = true;
            for(int i=0;i<n;i++){
                if(seen[X[i][j]]){ perm=false; break; }
                seen[X[i][j]]=1;
            }
            if(perm){ badCols.push_back(j); colBad[j]=1; }
        }
        int a = (int)badRows.size(), b = (int)badCols.size();
        int m = max(a, b);
        vector<int> goodRows, goodCols;
        for(int i=0;i<n;i++) if(!rowBad[i]) goodRows.push_back(i);
        for(int j=0;j<n;j++) if(!colBad[j]) goodCols.push_back(j);

        vector<array<int,3>> ops;
        int pairs = min(a, b);
        for(int k=0;k<pairs;k++){
            int i = badRows[k], j = badCols[k];
            int v = X[i][j];
            int w = v % n + 1;
            ops.push_back({i+1, j+1, w});
        }
        if(a > b){
            int gi = 0;
            for(int k=b;k<a;k++){
                int i = badRows[k];
                int j = goodCols[gi++];
                int v = X[i][j];
                int w = -1;
                for(int r=0;r<n;r++){
                    if(r==i) continue;
                    if(X[r][j] != v){ w = X[r][j]; break; }
                }
                if(w == -1) w = v % n + 1;
                ops.push_back({i+1, j+1, w});
            }
        } else if(b > a){
            int ri = 0;
            for(int k=a;k<b;k++){
                int j = badCols[k];
                int i = goodRows[ri++];
                int v = X[i][j];
                int w = -1;
                for(int c=0;c<n;c++){
                    if(c==j) continue;
                    if(X[i][c] != v){ w = X[i][c]; break; }
                }
                if(w == -1) w = v % n + 1;
                ops.push_back({i+1, j+1, w});
            }
        }
        printf("%d\n", m);
        for(auto &op: ops){
            printf("%d %d %d\n", op[0], op[1], op[2]);
        }
    }
    return 0;
}
```
