# [ICPC 2011 Beijing R] Matrix 矩阵哈希

## 题目描述
给定一个 $M$ 行 $N$ 列的 $01$ 矩阵，以及 $Q$ 个 $A$ 行 $B$ 列的 $01$ 矩阵，你需要求出这 $Q$ 个矩阵哪些在原矩阵中出现过。 

所谓 $01$ 矩阵，就是矩阵中所有元素不是 $0$ 就是 $1$。

## 输入格式
输入文件的第一行为 $M,N,A,B$，参见题目描述。 

接下来 $M$ 行，每行 $N$ 个字符，非 $0$ 即 $1$ ，描述原矩阵。 

接下来一行为你要处理的询问数 $Q$。

接下来 $Q$ 个矩阵，一共 $Q\times A$ 行，每行 $B$ 个字符，描述 $Q$ 个 $01$ 矩阵。

## 输出格式
你需要输出 $Q$ 行，每行为 $0$ 或者 $1$，表示这个矩阵是否出现过，$0$ 表示没有出现过，$1$ 表示出现过。

## 样例
### 样例 1
```
3 3 2 2
111
000
111
3
11
00
11
11
00
11
```
```
1
0
1
```

## 提示
对于 $100\%$ 的实际测试数据，$1\leq M,N \leq 1000$，$Q = 1000$。 

对于 $40\%$ 的数据，$A = 1$。

对于 $80\%$ 的数据，$A \leq 10$。

对于 $100\%$ 的数据，$A \leq 100$。

## 解题思路
### 问题分析
Q 个 A×B 的 01 矩阵是否在大 M×N 矩阵中出现过。

### 核心思路
二维字符串哈希。预处理大矩阵的所有 A×B 子矩阵哈希值。

### 算法流程
1. 读入 M,N 和大矩阵
2. 计算二维哈希
3. 读入 Q 和小矩阵
4. 计算小矩阵哈希，查集合

### 复杂度分析
- 时间复杂度：O(MN + QAB)
- 空间复杂度：O(MN)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

typedef unsigned long long ULL;
const ULL P1 = 131, P2 = 137;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int M, N; cin >> M >> N;
    vector<string> mat(M);
    for (int i = 0; i < M; i++) cin >> mat[i];
    
    vector<ULL> pow1(N + 1, 1), pow2(M + 1, 1);
    for (int i = 1; i <= N; i++) pow1[i] = pow1[i-1] * P1;
    for (int i = 1; i <= M; i++) pow2[i] = pow2[i-1] * P2;
    
    vector<vector<ULL>> h(M + 1, vector<ULL>(N + 1, 0));
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
            h[i][j] = h[i-1][j] * P2 + h[i][j-1] * P1 - h[i-1][j-1] * P1 * P2 + (mat[i-1][j-1] - '0');
    
    auto get_hash = [&](int x1, int y1, int x2, int y2) {
        return h[x2][y2] - h[x1-1][y2] * pow2[x2-x1+1] - h[x2][y1-1] * pow1[y2-y1+1] + h[x1-1][y1-1] * pow2[x2-x1+1] * pow1[y2-y1+1];
    };
    
    int Q; cin >> Q;
    while (Q--) {
        int A, B; cin >> A >> B;
        ULL target = 0;
        for (int i = 1; i <= A; i++) {
            string s; cin >> s;
            for (int j = 1; j <= B; j++)
                target = target * P1 + (s[j-1] - '0');
        }
        
        bool found = false;
        for (int i = 1; i + A - 1 <= M && !found; i++)
            for (int j = 1; j + B - 1 <= N && !found; j++)
                if (get_hash(i, j, i + A - 1, j + B - 1) == target)
                    found = true;
        cout << (found ? "1" : "0") << "\n";
    }
    return 0;
}
```
