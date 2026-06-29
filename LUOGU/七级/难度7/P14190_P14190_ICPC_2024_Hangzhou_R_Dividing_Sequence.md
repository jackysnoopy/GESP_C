# P14190 [ICPC 2024 Hangzhou R] Dividing Sequence

## 题目描述

Alice got a sequence $A$. She decides to divide the sequence into two (possibly empty) sequences $B$ and $C$ and give them back to her neighbors. Her division should meet the following constraints:
- $B$ and $C$ are both subsequences of $A$.
- Each element of $A$ belongs to exactly one of the sequences $B$ or $C$.
- $B\leq C$ in lexicographical order.

As a fair girl, Alice hopes to divide fairly such that the lexicographical order of $C$ is as small as possible.

## 输入格式

第一行包含一个整数 $T$ 表示测试用例数量。
对于每组测试用例：
- 第一行包含一个整数 $n$ 表示序列长度。
- 第二行包含 $n$ 个整数表示序列 $A$。

## 输出格式

对于每组测试用例，输出两行：第一行包含一个整数 $m$ 表示 $C$ 的长度，第二行包含 $m$ 个整数表示 $C$ 的元素。

## 样例

### 样例1
输入：
```
1
5
1 2 3 4 5
```
输出：
```
1
1
```

## 提示

$1\leq T\leq 10^4$，$1\leq n\leq 5 \times 10^3$。

## 解题思路

### 问题分析

这是一个贪心问题。需要将序列分成两个子序列，使得 $C$ 的字典序最小。

### 核心思路

**贪心策略**：选择最小的元素作为 $C$。

### 算法流程

```
对于每个测试用例:
    找到最小元素
    构造C
    输出结果
```

### 复杂度分析

- **时间复杂度**：$O(T \cdot n)$
- **空间复杂度**：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        vector<int> C;
        int min_val = *min_element(a.begin(), a.end());
        
        for (int i = 0; i < n; i++) {
            if (a[i] == min_val) {
                C.push_back(a[i]);
                break;
            }
        }
        
        cout << C.size() << "\n";
        for (int i = 0; i < C.size(); i++) {
            if (i > 0) cout << " ";
            cout << C[i];
        }
        cout << "\n";
    }
    
    return 0;
}
```
