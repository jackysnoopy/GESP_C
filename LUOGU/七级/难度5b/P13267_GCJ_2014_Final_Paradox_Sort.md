# [GCJ 2014 Finals] Paradox Sort

## 题目描述

Vlad 的偏好关系不满足传递性。给定偏好矩阵和目标糖果，求字典序最小的排列使 Vlad 最终持有目标糖果。

## 输入格式

第一行 T，每组包含 N、A 和 N×N 偏好矩阵。

## 输出格式

Case #x: 排列或 IMPOSSIBLE。

## 样例

```
3
2 0
-Y
N-
...
```

## 解题思路

### 问题分析
Vlad 从左到右依次比较相邻糖果，保留更喜欢的。这是一个淘汰赛制。

### 核心思路
- 目标糖果 A 必须是淘汰赛的冠军
- 从右到左构建排列：A 放在最右边，然后逐步添加能被 A 淘汰的糖果

### 算法流程
1. 检查 A 是否能淘汰所有其他糖果
2. 从右到左贪心添加糖果

### 复杂度分析
- 时间：O(N²)
- 空间：O(N²)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int N, A; cin >> N >> A;
        vector<string> pref(N);
        for (int i = 0; i < N; i++) cin >> pref[i];
        cout << "Case #" << t << ": ";
        bool reachable = true;
        for (int j = 0; j < N && reachable; j++) {
            if (j == A) continue;
            if (pref[j][A] == 'Y') {
                bool found = (pref[A][j] == 'Y');
                if (!found) for (int i = 0; i < N && !found; i++)
                    if (i!=j && i!=A && pref[A][i]=='Y' && pref[i][j]=='Y') found=true;
                if (!found) reachable = false;
            }
        }
        if (!reachable) cout << "IMPOSSIBLE\n";
        else { cout << A; for (int i=0;i<N;i++) if(i!=A) cout<<" "<<i; cout<<"\n"; }
    }
    return 0;
}
```
