# [GCJ 2013 Qualification] Lawnmower

## 题目描述

Alice 和 Bob 有一块 $N\times M$ 的草坪，初始草高均为 100 毫米。他们有一台割草机：可在草坪外设定高度 $h\in[1,100]$，然后从某条边垂直进入、沿直线割到对边出，把沿途高于 $h$ 的草都削到 $h$（1 米宽的一道）。每次只能在草坪外调高度。

给定一个目标图案（每个 $1\times1$ 方格的目标草高），判断是否可能割出该图案。

## 输入格式

第一行 $T$。每组第一行 $N,M$；随后 $N$ 行每行 $M$ 个整数 $a_{i,j}$ 为目标高度。

## 输出格式

每组输出 `Case #x: y`，$y$ 为 `YES` 或 `NO`。

## 提示

- $1\le T\le100$，$1\le N,M\le100$，$1\le a_{i,j}\le100$。
- 割草机只能“降低”草高，不能升高。一次行割把整行所有高于 $h$ 的格子降到 $h$；一次列割同理。
- 样例 1（`2 1 2 / 1 1 1 / 2 1 2`）可行：四角为 2 的行/列用 $h=2$ 割，中间用 $h=1$ 割。样例 2 中间格 $(2,2)=1$ 但同行同列最大值都是 2，无法实现。样例 3 单行 `1 2 1` 可行。

## 解题思路

### 问题分析

对某一行多次行割，等价于取所用高度的最小值 $R_i$（不割则 $R_i=100$）；对某一列多次列割等价于取最小值 $C_j$。方格 $(i,j)$ 的最终高度恰为 $\min(R_i,C_j)$（行割与列割取下确界）。因此图案可达成 $\iff$ 存在 $R_i,C_j\in[1,100]$ 使得 $a_{i,j}=\min(R_i,C_j)$ 对所有 $(i,j)$ 成立。

### 核心思路

对每个方格，$\min(R_i,C_j)=a_{i,j}$ 要求 $R_i\ge a_{i,j}$ 且 $C_j\ge a_{i,j}$，且至少一个等于 $a_{i,j}$。因此 $R_i$ 至少要等于该行最大值（$R_i\ge\max_j a_{i,j}$），取最紧的 $R_i=\max_j a_{i,j}$（行最大值）；同理 $C_j=\max_i a_{i,j}$（列最大值）。这是最严格也最可能成功的取法。

判定：对所有 $(i,j)$ 检查 $a_{i,j}=\min(R_i,C_j)$ 是否成立。全部成立则 `YES`，否则 `NO`。

### 算法流程

1. 读入网格，计算每行最大值 `rowmax[i]`、每列最大值 `colmax[j]`。
2. 遍历每个格点，若 $a_{i,j}\ne\min(\text{rowmax}[i],\text{colmax}[j])$ 则不可行。
3. 输出 `YES`/`NO`。

### 复杂度分析

读入与判定均为 $O(NM)$，空间 $O(NM)$。$N,M\le100$，极快。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int T; cin >> T;
    for(int tc=1; tc<=T; ++tc){
        int N, M; cin >> N >> M;
        vector<vector<int>> a(N, vector<int>(M));
        vector<int> rowmax(N, 0), colmax(M, 0);
        for(int i=0; i<N; ++i){
            for(int j=0; j<M; ++j){
                cin >> a[i][j];
                rowmax[i] = max(rowmax[i], a[i][j]);
                colmax[j] = max(colmax[j], a[i][j]);
            }
        }
        bool ok = true;
        for(int i=0; i<N && ok; ++i){
            for(int j=0; j<M; ++j){
                if(a[i][j] != min(rowmax[i], colmax[j])){
                    ok = false;
                    break;
                }
            }
        }
        cout << "Case #" << tc << ": " << (ok ? "YES" : "NO") << "\n";
    }
    return 0;
}
```
