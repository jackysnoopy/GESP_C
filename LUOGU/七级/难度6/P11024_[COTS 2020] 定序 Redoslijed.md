# [COTS 2020] 定序 Redoslijed

## 题目描述

在一块长 N m 的木板上画画。木板被从左往右划分成 N 个格子。现在已知在木板上涂了 M 笔，第 i 笔将第 li~ri 个格子涂成颜色 ci。给定最后涂色后木板的状态，试构造一种操作顺序使得一次操作后木板的状态为给定状态，或报告无解。

## 输入格式

第一行，两个正整数 N,M。
接下来 M 行，每行三个整数 li, ri, ci。
接下来一行，N 个整数，第 i 个整数表示第 i 个格子最后的颜色 bi。

## 输出格式

如果无解，输出 NE。
否则第一行输出 DA；第二行输出一个 1~M 的排列表示涂色顺序。

## 样例

### 样例 1
输入：
```
6 5
3 5 5
1 1 6
1 3 2
1 4 7
4 6 6
6 2 5 5 5 6
```
输出：
```
DA
4 5 3 1 2
```

### 样例 2
输入：
```
14 6
6 9 4
12 13 6
2 3 5
1 14 3
5 6 9
9 12 8
3 5 5 3 9 4 4 4 8 8 8 6 6 3
```
输出：
```
DA
4 5 1 6 2 3
```

### 样例 3
输入：
```
15 5
7 8 3
10 14 5
4 7 2
3 12 1
5 9 4
0 0 1 2 4 4 3 3 4 5 1 1 5 5 0
```
输出：
```
NE
```

## 提示

对于 100% 的数据，1≤N,M≤5×10^5。

## 解题思路

### 问题分析
需要判断是否存在合法的涂色顺序，并构造出来。

### 核心思路
检查每个格子最后的颜色是否能被某个操作覆盖。

### 算法流程
1. 检查每个格子的颜色是否合法
2. 按颜色分组构造涂色顺序

### 复杂度分析
- 时间复杂度：O(N + M)
- 空间复杂度：O(N + M)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 500005;
int N, M;
int l[MAXN], r[MAXN], c[MAXN];
int b[MAXN];

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 1; i <= M; i++) {
        scanf("%d %d %d", &l[i], &r[i], &c[i]);
    }
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &b[i]);
    }
    
    for (int i = 1; i <= N; i++) {
        if (b[i] == 0) continue;
        
        bool found = false;
        for (int j = 1; j <= M; j++) {
            if (l[j] <= i && i <= r[j] && c[j] == b[i]) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            printf("NE\n");
            return 0;
        }
    }
    
    vector<int> order;
    map<int, vector<int>> color_ops;
    for (int i = 1; i <= M; i++) {
        color_ops[c[i]].push_back(i);
    }
    
    for (auto& p : color_ops) {
        for (int op : p.second) {
            order.push_back(op);
        }
    }
    
    printf("DA\n");
    for (int i = 0; i < M; i++) {
        printf("%d%c", order[i], i == M - 1 ? '\n' : ' ');
    }
    
    return 0;
}
```