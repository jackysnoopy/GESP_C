# The Pilots Brothers' refrigerator

## 题目描述
The game “The Pilots Brothers: following the stripy elephant” has a quest where a player needs to open a refrigerator.

There are $16$ handles on the refrigerator door. Every handle can be in one of two states: open or closed. The refrigerator is open only when all handles are open. The handles are represented as a matrix $4\times4$. You can change the state of a handle in any location $[i, j] (1 \leq i, j \leq 4)$. However, this also changes states of all handles in row $i$ and all handles in column $j$.

The task is to determine the minimum number of handle switching necessary to open the refrigerator.

## 输入格式
The input contains four lines. Each of the four lines contains four characters describing the initial state of appropriate handles. A symbol “+” means that the handle is in closed state, whereas the symbol “−” means “open”. At least one of the handles is initially closed.

## 输出格式
The first line of the input contains $N$ – the minimum number of switching. The rest $N$ lines describe switching sequence. Each of the lines contains a row number and a column number of the matrix separated by one or more spaces. If there are several solutions, you may give any one of them.

## 样例
### 样例 1
```
-+--
----
----
-+--
```
```
6 
1 1 
1 3 
1 4 
4 1 
4 3 
4 4
```

## 解题思路
### 问题分析
4×4 冰箱门开关，按一个会翻转同行同列所有开关。求从初始状态到全关的最少步数及方案。

### 核心思路
每个开关最多按一次。用二进制枚举 4×4=16 个开关的状态（2^16=65536），检查是否可行，取最少步数。

### 算法流程
1. 读入 4×4 初始状态（+ 关，- 开）
2. 枚举 mask=0..(1<<16)-1
3. 对每种方案模拟操作
4. 若结果全关，比较步数
5. 输出最少步数及坐标

### 复杂度分析
- 时间复杂度：O(2^16 × 4²) = O(1)
- 空间复杂度：O(1)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int a[4][4];

void press(int x, int y) {
    for (int i = 0; i < 4; i++) {
        a[x][i] ^= 1;
        a[i][y] ^= 1;
    }
    a[x][y] ^= 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int init = 0;
    for (int i = 0; i < 4; i++) {
        string s; cin >> s;
        for (int j = 0; j < 4; j++)
            if (s[j] == '+') init |= (1 << (i * 4 + j));
    }
    
    int ans_mask = 0, ans_cnt = INT_MAX;
    for (int mask = 0; mask < (1 << 16); mask++) {
        int cur = init;
        int cnt = 0;
        for (int pos = 0; pos < 16; pos++) {
            if (mask >> pos & 1) {
                cnt++;
                int x = pos / 4, y = pos % 4;
                for (int k = 0; k < 4; k++) {
                    cur ^= (1 << (x * 4 + k));
                    cur ^= (1 << (k * 4 + y));
                }
                cur ^= (1 << pos);
            }
        }
        if (cur == 0 && cnt < ans_cnt) {
            ans_cnt = cnt;
            ans_mask = mask;
        }
    }
    
    cout << ans_cnt << "\n";
    for (int pos = 0; pos < 16; pos++)
        if (ans_mask >> pos & 1)
            cout << pos / 4 + 1 << " " << pos % 4 + 1 << "\n";
    return 0;
}
```
