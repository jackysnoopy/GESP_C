# [ICPC 2024 APC] Duplicates

## 题目描述

我们称一个数字序列**含有重复元素**，如果序列中存在出现一次以上的元素。形式化地讲，一个序列 $(a_1, \dots, a_n)$ 含有重复元素，如果存在两个不等的下标 $i$ 和 $j$ 使得 $a_i = a_j$。

给定一个 $n \times n$ 的矩阵 $X$。$X$ 中的每个元素都是一个 $1$ 到 $n$ 之间（含两端）的整数。你可以将 $X$ 中零个或多个元素修改为 $1$ 到 $n$ 之间（含两端）的任意整数。不同的元素可以修改为不同的整数。

你的任务是通过修改 $X$ 中的元素，使得以下所有条件都成立：

* 对于每一行 $i$，序列 $(X_{i1}, X_{i2}, \dots, X_{in})$ 含有重复元素。
* 对于每一列 $j$，序列 $(X_{1j}, X_{2j}, \dots, X_{nj})$ 含有重复元素。

你需要计算达成此目标所需的**最小**修改次数。同时，找出一种可行的修改方案。对于每次修改，你需要指明修改的是哪个元素以及它的新值。请注意，当给定的矩阵 $X$ 已经满足上述条件时，所需的最小修改次数可以为零。

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 1000$），代表测试用例的数量。之后是 $t$ 个测试用例。每个测试用例的格式如下。

一个测试用例的第一行包含一个整数 $n$（$3 \le n \le 100$）。
接下来的 $n$ 行，每行包含 $n$ 个整数。第 $i$ 行的第 $j$ 个整数代表 $X_{ij}$（$1 \le X_{ij} \le n$）。

在单个输入文件中，所有测试用例的 $n^2$ 的总和不超过 $10,000$。

## 输出格式

对于每个测试用例，按以下格式输出一组修改方案。

第一行输出一个整数 $m$，代表需要修改的元素的最小数量。
在接下来的 $m$ 行中，每行输出三个整数 $i, j, v$。这代表一次修改，即将元素 $X_{ij}$ 的值修改为 $v$。这三个整数都必须在 $1$ 和 $n$ 之间（含两端）。

如果存在多种解法，你可以输出其中任意一种。

## 样例

### 样例输入 1
```
5
4
3 2 1 1
2 1 3 4
1 3 3 1
4 4 4 2
3
1 3 1
2 1 3
3 2 2
5
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
3
1 1 2
2 2 1
2 3 2
3
1 1 3
3 2 1
3 1 3
```

### 样例输出 1
```
2
2 1 1
4 2 3
3
2 1 3
2 2 3
3 3 3
0
1
1 2 2
1
2 1 1
```

## 提示

**样例解释 #1**

在第一个测试用例中，修改后的矩阵如下所示。

$$
\begin{bmatrix}
3 & 2 & 1 & 1 \\
1 & 1 & 3 & 4 \\
1 & 3 & 3 & 1 \\
4 & 3 & 4 & 2 \\
\end{bmatrix}
$$

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