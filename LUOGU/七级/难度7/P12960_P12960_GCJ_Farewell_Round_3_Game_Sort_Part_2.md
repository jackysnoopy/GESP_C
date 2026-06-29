# P12960 [GCJ Farewell Round #3] Game Sort: Part 2

## 题目描述

Amir and Badari are playing a sorting game. The game starts with a string $\mathbf{S}$ and an integer $\mathbf{P}$. Amir has to split $\mathbf{S}$ into exactly $\mathbf{P}$ contiguous non-empty parts. Then, Badari must rearrange the letters within each part to make the list of parts be sorted in non-decreasing lexicographical order.

Given the initial string and number of parts, can you help Amir win the game by choosing his parts in a way Badari cannot win herself?

## 输入格式

第一行输入测试用例数量 $T$。每行描述一个测试用例，包含一个整数 $\mathbf{P}$ 和一个字符串 $\mathbf{S}$。

## 输出格式

对于每个测试用例，输出一行包含 `Case #x: y`，其中 $y$ 是 `POSSIBLE` 或 `IMPOSSIBLE`。如果可能，输出第二行包含分割结果。

## 样例

### 样例1
输入：
```
3
3 ODEJAM
3 AAA
3 CODEJAM
```
输出：
```
Case #1: POSSIBLE
O DEJAM
Case #2: POSSIBLE
AAA
Case #3: IMPOSSIBLE
```

## 提示

$1 \leq \mathbf{T} \leq 100$。

## 解题思路

### 问题分析

这是一个博弈论问题。Amir需要找到一种分割方式，使得Badari无法排序。

### 核心思路

**贪心构造**：尝试找到一种分割，使得某些部分无法通过重排变得有序。

### 算法流程

```
对于每个测试用例:
    检查是否可能
    如果可能，构造分割
    否则输出IMPOSSIBLE
```

### 复杂度分析

- **时间复杂度**：$O(T \cdot n)$
- **空间复杂度**：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int P;
        string S;
        cin >> P >> S;
        
        int n = S.length();
        
        bool possible = true;
        
        if (P >= n) {
            possible = false;
        }
        
        bool all_same = true;
        for (int i = 1; i < n; i++) {
            if (S[i] != S[0]) {
                all_same = false;
                break;
            }
        }
        if (all_same && P > 1) {
            possible = false;
        }
        
        if (possible) {
            cout << "Case #" << t << ": POSSIBLE\n";
            
            vector<int> splits;
            int part_size = n / P;
            int remainder = n % P;
            
            int pos = 0;
            for (int i = 0; i < P; i++) {
                int len = part_size + (i < remainder ? 1 : 0);
                splits.push_back(len);
            }
            
            pos = 0;
            for (int i = 0; i < P; i++) {
                cout << S.substr(pos, splits[i]);
                if (i < P - 1) cout << " ";
                pos += splits[i];
            }
            cout << "\n";
        } else {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
        }
    }
    
    return 0;
}
```
