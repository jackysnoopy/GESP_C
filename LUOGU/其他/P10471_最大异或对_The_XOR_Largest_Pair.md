# 最大异或对 The XOR Largest Pair

## 题目描述
给定 $N$ 个整数 $A_1,A_2, \cdots, A_N$ 中选出两个进行异或计算，得到的结果最大是多少？

## 输入格式
第一行一个整数 $N$，第二行 $N$ 个整数 $A_1,A_2, \cdots, A_N$。

## 输出格式
一个整数表示答案。

## 样例
### 样例 1
```
3
1 2 3
```
```
3
```

## 提示
对于所有测试数据，$1 \le N \le 10^5$，保证 $0\le A_i<2^{31}$。

## 解题思路
### 问题分析
N 个数中选两个异或的最大值。

### 核心思路
Trie 树。将所有数按二进制插 Trie，对每个数在 Trie 中尽量走相反的位。

### 算法流程
1. 读入 N 和数组
2. 将所有数插入 01-Trie
3. 对每个数，在 Trie 中优先走相反的位
4. 更新最大值

### 复杂度分析
- 时间复杂度：O(N log C)
- 空间复杂度：O(N log C)

## 参考代码
```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100005 * 31;
int trie[MAXN][2], tot = 1;

void insert(int x) {
    int p = 1;
    for (int i = 30; i >= 0; i--) {
        int b = (x >> i) & 1;
        if (!trie[p][b]) trie[p][b] = ++tot;
        p = trie[p][b];
    }
}

int query(int x) {
    int p = 1, res = 0;
    for (int i = 30; i >= 0; i--) {
        int b = (x >> i) & 1;
        if (trie[p][b ^ 1]) {
            res |= (1 << i);
            p = trie[p][b ^ 1];
        } else {
            p = trie[p][b];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        insert(a[i]);
    }
    
    int ans = 0;
    for (int x : a) ans = max(ans, query(x));
    cout << ans << "\n";
    return 0;
}
```
