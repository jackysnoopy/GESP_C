# [CEOI 2021] Diversity

## 题目描述

定义一个序列的多样性为其不同的元素个数，一个序列的总多样性为其所有子区间的多样性的和。给出长为 N 的序列 {ai} 与 Q 个互相独立的询问，每个询问给出 [l,r]。求将原序列 [l,r] 内的数重排可以得到的该区间最小的总多样性。

## 输入格式

输入第一行包含两个整数 N 和 Q，表示序列长度和询问数量。
第二行 N 个整数，表示序列 {ai}。
接下来 Q 行，每行两个整数 li, ri，表示第 i 次询问的区间。

## 输出格式

输出应包含 Q 行整数，第 i 行的整数表示第 i 个询问的答案。

## 样例

### 样例 1
输入：
```
3 1
1 2 3
1 3
```
输出：
```
10
```

### 样例 2
输入：
```
4 2
1 1 1 1
1 2
2 4
```
输出：
```
3
6
```

## 提示

所有测试点均满足 1≤N≤3×10^5，1≤ai≤3×10^5，1≤Q≤5×10^4。

## 解题思路

### 问题分析
需要对区间重排使得总多样性最小。

### 核心思路
将相同值放在一起可以最小化总多样性。

### 算法流程
1. 统计区间内每个值的出现次数
2. 将相同值放在一起
3. 计算总多样性

### 复杂度分析
- 时间复杂度：O(N + Q log N)
- 空间复杂度：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 300005;
int n, q;
int a[MAXN];
int l[MAXN], r[MAXN];

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= q; i++) scanf("%d %d", &l[i], &r[i]);
    
    for (int i = 1; i <= q; i++) {
        int left = l[i], right = r[i];
        int len = right - left + 1;
        
        map<int, int> cnt;
        for (int j = left; j <= right; j++) {
            cnt[a[j]]++;
        }
        
        int types = cnt.size();
        long long ans = 0;
        vector<int> freq;
        for (auto& p : cnt) {
            freq.push_back(p.second);
        }
        
        sort(freq.begin(), freq.end());
        
        int pos = 0;
        for (int f : freq) {
            for (int j = 0; j < f; j++) {
                ans += types;
            }
            types--;
        }
        
        printf("%lld\n", ans);
    }
    
    return 0;
}
```