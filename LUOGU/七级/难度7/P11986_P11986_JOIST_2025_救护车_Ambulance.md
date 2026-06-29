# P11986 [JOIST 2025] 救护车 / Ambulance

## 题目描述

IOI 王国被表示为一个 $L$ 行 $L$ 列的方形网格。在网格的四个角落各建造一所医院，每所医院配备一辆救护车。

救护车运输规则如下：
- 救护车可在时间 $0$ 或之后开始移动。
- 救护车一次**最多**运送 $1$ 名患者。
- 救护车只能将患者送回其初始所属医院。
- 救护车每次移动到四连通单元格耗时 $1$ 单位时间。

已知第 $k$ 名患者位于 $(X_k, Y_k)$，判断是否所有患者都能在时间 $T$ 内被运送到任意医院。

## 输入格式

$L$ $N$ $T$
$X_1$ $Y_1$
$X_2$ $Y_2$
$\vdots$
$X_N$ $Y_N$

## 输出格式

若所有患者可在时间 $T$ 内被送医，输出 $\texttt{Yes}$；否则输出 $\texttt{No}$。

## 样例

### 样例1
输入：
```
6 4 8
1 2
3 3
4 4
5 6
```
输出：
```
Yes
```

## 提示

- $1 \leq L \leq 10^9$；
- $1 \leq N \leq 10^5$；
- $1 \leq T \leq 10^9$。

## 解题思路

### 问题分析

这是一个贪心问题。需要判断所有患者是否能在时间 $T$ 内被运送到医院。

### 核心思路

**贪心策略**：每个患者选择最近的医院。

### 算法流程

```
对于每个患者:
    计算到4个医院的距离
    选择最近的医院
检查是否所有患者都能在时间T内被运送
```

### 复杂度分析

- **时间复杂度**：$O(N)$
- **空间复杂度**：$O(N)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int L, N, T;
    cin >> L >> N >> T;
    
    vector<int> X(N), Y(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
    }
    
    vector<pair<int, int>> hospitals = {
        {1, 1}, {1, L}, {L, 1}, {L, L}
    };
    
    vector<vector<int>> dist(N, vector<int>(4));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++) {
            dist[i][j] = abs(X[i] - hospitals[j].first) + abs(Y[i] - hospitals[j].second);
        }
    }
    
    bool possible = true;
    for (int i = 0; i < N; i++) {
        int min_dist = *min_element(dist[i].begin(), dist[i].end());
        if (min_dist > T) {
            possible = false;
            break;
        }
    }
    
    if (possible) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    
    return 0;
}
```
