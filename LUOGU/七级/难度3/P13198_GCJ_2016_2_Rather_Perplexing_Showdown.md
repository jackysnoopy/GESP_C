# [GCJ 2016 #2] Rather Perplexing Showdown

## 题目描述

You've been asked to organize a Rock-Paper-Scissors tournament. The tournament will have a single-elimination format and will run for $\mathrm{N}$ rounds; $2^{\mathrm{N}}$ players will participate.

Initially, the players will be lined up from left to right in some order that you specify. In each round, the first and second players in the lineup (starting from the left) will play a match against each other, and the third and fourth players in the lineup (if they exist) will play a match against each other, and so on; all of these matches will occur simultaneously. The winners of these matches will remain in the lineup, in the same relative order, and the losers will leave the lineup and go home. Then a new round will begin. This will continue until only one player remains in the lineup; that player will be declared the winner.

In each Rock-Paper-Scissors match, each of the two players secretly chooses one of Rock, Paper, or Scissors, and then they compare their choices. Rock beats Scissors, Scissors beats Paper, and Paper beats Rock. If one player's choice beats the other players's choice, then that player wins and the match is over. However, if the players make the same choice, then it is a tie, and they must choose again and keep playing until there is a winner.

You know that the players this year are stubborn and not very strategic. Each one has a preferred move and will only play that move in every match, regardless of what the opponent does. Because of this, if two players with the same move go up against each other, they will keep tying and their match will go on forever! If this happens, the tournament will never end and you will be a laughingstock.

This year, there are $\mathbf{R}$ players who prefer Rock, $\mathbf{P}$ players who prefer Paper, and $\mathbf{S}$ players who prefer Scissors. Knowing this, you want to create a lineup that guarantees that the tournament will go to completion and produce a single winner — that is, no match will ever be a tie. Your boss has asked you to produce a list of all such lineups (written in left to right order, with $\mathrm{R}, \mathrm{P}$, and $\mathrm{S}$ standing for players who prefer Rock, Paper, and Scissors, respectively), and then put that list in alphabetical order.

You know that the boss will lazily pick the first lineup on the list; what will that be? Or do you have to tell your boss that it is IMPOSSIBLE to prevent a tie?

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ lines follow; each represents one test case. Each test case consists of four integers: $\mathbf{N}, \mathbf{R}, \mathbf{P}$, and $\mathbf{S}$, as described in the statement above.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is either IMPOSSIBLE or a string of length $2^{\mathrm{N}}$ representing the alphabetically earliest starting lineup that solves the problem. Every character in a lineup must be $\mathrm{R}, \mathrm{P}$, or $\mathrm{s}$, and there must be $\mathbf{R}$ `R`s, $\mathbf{P}$ `P`s, and $\mathbf{S}$ `S`s.

## 样例

### 样例输入 1
```
4
1 1 1 0
1 2 0 0
2 1 1 2
2 2 0 2
```

### 样例输出 1
```
Case #1: PR
Case #2: IMPOSSIBLE
Case #3: PSRS
Case #4: IMPOSSIBLE
```

## 提示

**Sample Explanation**

In sample case #1, there are only two players and the tournament will consist of one round. It doesn't matter what order the two line up in; the Paper-using player will defeat the Rock-using player. You will give your boss the alphabetically ordered list PR, RP, and the first element is PR.

In sample case #2, the only two players both play Rock, so a tie is unavoidable.

In sample case #3, there are four players and the tournament will go on for two rounds. In the first round, the first player (Paper) will lose to the second player (Scissors), and the third player (Rock) will defeat the fourth player (Scissors). The second round lineup will be PR, and the first remaining player (Paper) will defeat the other remaining player (Rock), so the tournament will end with a winner and no ties.

Here is an illustration of the tournament for sample case #3:

![](https://cdn.luogu.com.cn/upload/image_hosting/sr2g4apj.png)

Other lineups such as PSSR will appear on the list you give to your boss, but PSRS is alphabetically first.
In sample case #4, the only way to organize the first round such that there are no ties is to create two matches with one Rock player and one Scissors player. But both of those matches will have a Rock winner, and when these two winners go on to face each other, there will be a tie.

**Limits**

- $\mathbf{R}+\mathbf{P}+\mathbf{S}=2^{\mathbf{N}}$.
- $0 \leqslant \mathbf{R} \leqslant 2^{\mathbf{N}}$.
- $0 \leqslant \mathbf{P} \leqslant 2^{\mathbf{N}}$.
- $0 \leqslant \mathbf{S} \leqslant 2^{\mathbf{N}}$.

**Small dataset (4 Pts, Test Set 1 - Visible)**

- $1 \leqslant \mathbf{T} \leqslant 25$.
- $1 \leqslant \mathbf{N} \leqslant 3$.

**Large dataset (14 Pts, Test Set 2 - Hidden)**

- $1 \leqslant \mathbf{T} \leqslant 75$.
- $1 \leqslant \mathbf{N} \leqslant 12$.

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