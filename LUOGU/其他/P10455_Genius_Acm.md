# Genius Acm

## 题目描述
Advanced CPU Manufacturer (ACM) is one of the best CPU manufacturers in the world. 每天，该公司生产 $n$ 台 CPU 并销售到世界各地。

ACM 公司的质检部门会对生产出的 CPU 进行成组测试，对一组（若干个）CPU 进行测试的方法如下：

1. 随机从该组 CPU 中选取 $m$ 对（即 $2m$ 台），若总数不足 $2m$ 台，则选取尽量多对。

2. 对于每一对 CPU，测量它们之间的 Relative Performance Difference (RPD)，并把第 $i$ 对的 RPD 记为 $D_i$。RPD 的计算方法在后面给出。

3. 该组 CPU 的 Sqared Performance Difference (SPD） 由以下公式给出：

$SPD=\sum _i D^2_i$


4. 该组 CPU 通过质检，当且仅当 $SPD \le k,$ 其中 $k$ 是给定常数。

ACM 公司生产的 CPU 性能很好，而质检部门制定的标准更是过于严格。通常他们把 $n$ 台 CPU 作为一整组进行测试，这导致一些性能良好的 CPU 无法通过测试，生产部门对此颇有微词。作为质检部门的领导，小 S 在不更改质检测试流程的前提下，想出了这样一个主意：如果能够把 $n$ 台 CPU 恰当地分成连续的若干段，使得每段 CPU 都能够通过成组测试，就可以解决当下的问题。

现在，小 S 已经知道了 $n$ 台各自的性能表现 $P_1,\cdots ,P_n$，两台 CPU 的 RPD 被定义为它们性能表现的差的绝对值。请你帮忙计算一下，至少把这些 CPU 分成多少段，才能使得每一段都能通过成组测试。

## 输入格式
每个测试点包含多组数据，第一行整数 $T$ 给出数据组数。

对于每组数据，第一行三个整数 $n,m,k$，第二行 $n$ 个整数 $P_1,\cdots ,P_n$。

## 输出格式
对于每组数据，输出一个整数表示答案。

## 样例
### 样例 1
```
2
5 1 49
8 2 1 7 9
5 1 64
8 2 1 7 9
```
```
2
1
```

## 提示
对于 $20 \%$ 的数据，$1 \leq n \leq 10^2$ 。  
对于 $40 \%$ 的数据， $1 \leq n \leq 10^3$ 。  
对于另外 $10 \%$ 的数据，$k=0$ 。  
对于另外 $10 \%$ 的数据，$0 \leq k \leq 1$ 。  
对于另外 $10 \%$ 的数据， $m=1$ 。  
对于另外 $10 \%$ 的数据，$1 \leq m \leq 2$ 。  
对于 $90 \%$ 的数据，$0 \leq k \leq 10^{12}$ 。  
对于 $100 \%$ 的数据，$T \leq 12,1 \leq n, m \leq 5 \cdot 10^5, 0 \leq k \leq 10^{18}, 0 \leq P_i \leq 2^{20}$ 。

## 解题思路

### 问题分析
将 n 个元素的序列分为若干段，每段的"校验值"为取 M 对(最大-最小)²之和最大值。给定最大校验值 T，求最少分段数。

### 核心思路
贪心+倍增+排序。从左到右分段，每段尽可能长。用倍增法扩展区间，每次扩展后排序计算校验值。

### 算法流程
1. 读入 n, M, T 和序列
2. 从起点 start 开始，用倍增法确定最长可延伸的 end
3. 若校验值 ≤ T，加倍尝试；否则回退
4. 统计段数

### 复杂度分析
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int k;

long long check(const vector<int>& a, int l, int r) {
    vector<int> b(a.begin() + l, a.begin() + r + 1);
    sort(b.begin(), b.end());
    long long sum = 0;
    int len = b.size();
    for (int i = 0; i < k && i < len / 2; i++) {
        long long diff = b[len - 1 - i] - b[i];
        sum += diff * diff;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        long long lim;
        cin >> n >> m >> lim;
        k = m;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        int ans = 0, start = 0;
        while (start < n) {
            int len = 1, end = start;
            while (len > 0) {
                int next_end = min(n - 1, end + len);
                if (check(a, start, next_end) <= lim) {
                    end = next_end;
                    len *= 2;
                } else {
                    len /= 2;
                }
            }
            start = end + 1;
            ans++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
```
