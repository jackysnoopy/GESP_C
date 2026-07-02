# [GCJ 2014 Finals] Checkerboard Matrix

## 题目描述

通过交换行列将 2N×2N 二进制矩阵变为棋盘矩阵。

## 输入格式

第一行 T，每组包含 N 和 2N 行 01 字符串。

## 输出格式

Case #x: y，y 为最少交换次数或 IMPOSSIBLE。

## 样例

```
3
1
01
10
2
1001
0110
0110
1001
1
00
00
```

输出：
```
Case #1: 0
Case #2: 2
Case #3: IMPOSSIBLE
```

## 解题思路

### 问题分析
棋盘矩阵要求每行每列 01 交替。行交换和列交换独立，总次数 = 行交换 + 列交换。

### 核心思路
1. 检查每行是否恰好有 N 个 1（否则 IMPOSSIBLE）
2. 行分为两类互补模式（pattern A 和 pattern B）
3. 对每种形式（哪些行放偶数位）计算行交换 + 列交换数

### 算法流程
1. 统计每行 1 的个数
2. 提取行模式，检查只有两种互补模式
3. 枚举形式和选择，计算最优交换数

### 复杂度分析
- 时间：O(N²)
- 空间：O(N²)

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
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int N; cin >> N;
        vector<string> M(2*N);
        for (int i = 0; i < 2*N; i++) cin >> M[i];
        cout << "Case #" << t << ": ";
        bool ok = true;
        for (int i = 0; i < 2*N; i++) {
            int cnt = 0; for (char c : M[i]) cnt += (c=='1');
            if (cnt != N) { ok = false; break; }
        }
        if (!ok) { cout << "IMPOSSIBLE\n"; continue; }
        vector<int> pat(2*N, 0);
        for (int i = 0; i < 2*N; i++)
            for (int j = 0; j < 2*N; j++) if (M[i][j]=='1') pat[i]|=(1<<j);
        int p1=-1, p2=-1; vector<int> c1, c2;
        for (int i = 0; i < 2*N; i++) {
            if (p1==-1) { p1=pat[i]; c1.push_back(i); }
            else if (pat[i]==p1) c1.push_back(i);
            else if (p2==-1) { p2=pat[i]; c2.push_back(i); }
            else if (pat[i]==p2) c2.push_back(i);
            else { ok=false; break; }
        }
        if (!ok || p2==-1 || (p1^p2)!=(1<<(2*N))-1) { cout << "IMPOSSIBLE\n"; continue; }
        int ans = 2*N, fullM = (1<<(2*N))-1;
        int fullE = 0; for (int j=0;j<2*N;j+=2) fullE|=(1<<j);
        for (int form=0;form<2;form++) {
            int tgt = form==0 ? fullM^fullE : fullE;
            for (int ch=0;ch<2;ch++) {
                int tp = ch==0 ? p1 : p2;
                vector<int>& tr = ch==0 ? c1 : c2;
                int even=0; for (int r:tr) if (r%2==0) even++;
                int rs = N-even;
                int match = __builtin_popcount(tp&tgt);
                ans = min(ans, rs + N-match);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
```
