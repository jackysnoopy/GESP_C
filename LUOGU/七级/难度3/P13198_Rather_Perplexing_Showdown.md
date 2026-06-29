# [GCJ 2016 #2] Rather Perplexing Showdown

## 题目描述

你要组织一场石头剪刀布（Rock-Paper-Scissors）单淘汰锦标赛。比赛共进行 $N$ 轮，有 $2^N$ 名选手参赛。

选手最初按你指定的顺序从左到右排成一列。每一轮中，队列里第 1、2 名选手对战，第 3、4 名对战……所有对战同时进行。胜者按原相对顺序留在队列中，败者离开。如此继续，直到只剩一名选手，即为冠军。

每名选手有一个偏好的出拳（石头 R / 布 P / 剪刀 S），并且每场比赛都只会出这一个拳。石头胜剪刀，剪刀胜布，布胜石头。如果双方出拳相同，就会一直平局，比赛永远无法结束。

已知共有 $R$ 人偏好石头、$P$ 人偏好布、$S$ 人偏好剪刀（$R+P+S=2^N$）。请你找出所有“保证不会出现平局、能正常决出冠军”的排列，按字典序排序，输出字典序最小的那个；若不存在则输出 `IMPOSSIBLE`。

## 输入格式

第一行一个整数 $T$ 表示测试组数。接下来 $T$ 行，每行四个整数 $N, R, P, S$。

## 输出格式

每组输出一行 `Case #x: y`，其中 $y$ 为字典序最小的合法排列（长度 $2^N$ 的 R/P/S 串）或 `IMPOSSIBLE`。

## 提示

- $R+P+S=2^N$，$1\le N\le 12$，$1\le T\le 75$。
- 样例 1：$N=1$，2 人，PR 字典序最小。
- 样例 3：$N=2$，4 人，答案 `PSRS`：第一轮 P 负于 S、R 胜 S，第二轮 P 胜 R，全程无平局。
- 样例 4：两场都必须是 R 对 S，但两场都产生 R 冠军，决赛 R 对 R 必然平局，故 IMPOSSIBLE。

## 解题思路

### 问题分析

整场比赛是一个深度为 $N$ 的二叉淘汰树（括号赛制）。要保证“无平局”，每场比赛双方出拳必须不同。我们需要确定一个长度 $2^N$、由 R/P/S 组成且恰好含 $R$ 个 R、$P$ 个 P、$S$ 个 S 的字符串，使得按括号赛制进行时每场都不同拳，并在所有合法串中取字典序最小者。

### 核心思路

递归地看一棵深度为 $d$ 的子赛树。设它的冠军类型为 $w$。决赛是左右两棵深度 $d-1$ 子树的冠军对战；要让 $w$ 获胜，对手必须是 $w$ 所克制的类型 $L$（石头克剪刀、布克石头、剪刀克布）。因此：

- 一棵“冠军为 $w$、深度 $d$”的赛树，由“冠军为 $w$、深度 $d-1$”和“冠军为 $L$、深度 $d-1$”两棵子树拼接而成。
- 该赛树中 R/P/S 的数量 = 两棵子树数量之和（唯一确定）。
- 字典序最小的串 = 把两棵子树各自的最小串按两种顺序拼接，取较小者：$\min(s_w + s_L,\ s_L + s_w)$。

冠军类型确定后，整棵树中 R/P/S 的数量是唯一确定的；深度 $N$ 下三种冠军对应三个互不相同的数量三元组。所以对查询 $(R,P,S)$，只需检查哪个冠军 $w$ 的数量三元组恰好等于 $(R,P,S)$，取其最小串即可；都不匹配则 IMPOSSIBLE。

### 算法流程

1. 令类型编号 R=0, P=1, S=2，则 $w$ 克制的类型 $L=(w+2)\bmod 3$。
2. 预处理 `table[d][w]`：$d=0$ 时单字符、对应计数为 1；$d\ge1$ 时按递推合并两棵子树，计数相加，串取两顺序的字典序较小者。
3. 对每组查询 $(N,R,P,S)$，遍历 $w\in\{0,1,2\}$，若 `table[N][w]` 的计数等于 $(R,P,S)$，记录其串并取最小；无匹配则输出 `IMPOSSIBLE`。

### 复杂度分析

预处理 $O(N\cdot 2^N)$（串总长）。每组查询 $O(2^N)$ 比较。$N\le12$，串长 $\le4096$，十分宽裕。时间 $O(N\cdot2^N + T\cdot2^N)$，空间 $O(N\cdot2^N)$。

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    array<long long,3> cnt;
    string s;
};

int main(){
    const int MAXN = 12;
    // table[d][w]: depth d bracket whose overall winner is w (0=R,1=P,2=S)
    vector<vector<Node>> table(MAXN+1, vector<Node>(3));
    const char* ch = "RPS";
    for(int w=0; w<3; ++w){
        table[0][w].cnt = {0,0,0};
        table[0][w].cnt[w] = 1;
        table[0][w].s = string(1, ch[w]);
    }
    // w beats L; to make w win the final, the other half must produce L
    for(int d=1; d<=MAXN; ++d){
        for(int w=0; w<3; ++w){
            int L = (w+2)%3;            // the type that w beats
            Node &a = table[d-1][w];    // half producing w
            Node &b = table[d-1][L];    // half producing L
            for(int k=0; k<3; ++k) table[d][w].cnt[k] = a.cnt[k] + b.cnt[k];
            string s1 = a.s + b.s;
            string s2 = b.s + a.s;
            table[d][w].s = min(s1, s2);
        }
    }
    int T; cin >> T;
    for(int t=1; t<=T; ++t){
        int N; long long R, P, S;
        cin >> N >> R >> P >> S;
        string best;
        bool found = false;
        for(int w=0; w<3; ++w){
            if(table[N][w].cnt[0]==R && table[N][w].cnt[1]==P && table[N][w].cnt[2]==S){
                if(!found || table[N][w].s < best){
                    best = table[N][w].s;
                    found = true;
                }
            }
        }
        cout << "Case #" << t << ": " << (found ? best : string("IMPOSSIBLE")) << "\n";
    }
    return 0;
}
```
