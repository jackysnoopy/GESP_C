# [NWRRC 2023] Jumping Frogs

## 题目描述

Julia 拍了两张河面睡莲与青蛙的照片，两次拍照位置相同，且都有 n 只青蛙分别坐在 n 片睡莲上，每片睡莲最多一只青蛙。睡莲从左到右编号为 1,2,3,…。

对比两张照片发现：所有青蛙都移动了——没有任何一片睡莲在两张照片里都被占据（两组位置完全不相交）。青蛙彼此长得一样，无法对应。每只青蛙都跳到了另一片睡莲：有的向左（编号变小），有的向右（编号变大）。

Julia 想知道：两张照片之间**有多少只青蛙向左跳**？由于可能没有唯一答案，需要求出**所有可能**的答案。

## 输入格式

第一行一个整数 n（1 ≤ n ≤ 200000）。
第二行 n 个严格递增整数 a_1<...<a_n，表示第一张照片中青蛙所在的睡莲编号。
第三行 n 个严格递增整数 b_1<...<b_n，表示第二张照片中青蛙所在的睡莲编号。
所有 2n 个整数互不相同。

## 输出格式

第一行一个整数 k，表示可能答案的个数。
第二行 k 个递增整数 c_1<c_2<...<c_k，表示所有可能的"向左跳的青蛙数"。

## 提示

样例解释：样例 1 中落到睡莲 1、2 的青蛙必然来自更大的编号（向左），落到 51、52 的必然来自更小编号（向右），故向左数确定为 2。

## 解题思路

### 问题分析

青蛙不可区分，因此任意一个 a 到 b 的一一对应（双射）都是合法的移动方案。"向左跳"指被匹配的 b < a。我们要在所有双射下，求"向左跳对数"能取到哪些值。

设 L 为向左跳的对数。问题等价于：在 a 与 b 的所有匹配中，L 的最小值 mn 与最大值 mx 各是多少，以及两者之间是否所有整数都可达。

- 最小化 L ⇔ 最大化"向右跳（b > a）"的匹配数：把 a 升序，对每个 a 找最小的可用 b ≥ a 来配对，能配则配（向右），配不上则只能向左（mn++）。这是经典的二分配对贪心。
- 最大化 L ⇔ 最大化"向左跳（b < a）"的匹配数：把 a 降序，对每个 a 找最大的可用 b < a 来配对，能配则配（向左，mx++）。

可以证明：从最小匹配出发，通过一系列"交换两只青蛙归宿"的局部操作，可使 L 每次恰好变化 1，从而 [mn, mx] 中的每个整数都可达。因此答案集合就是闭区间 [mn, mx] 的所有整数。

### 核心思路

用两次贪心分别求出向左跳对数的最小值 mn 与最大值 mx，答案即为 [mn, mx] 内所有整数。最小值用"升序 a + lower_bound 找 b≥a"求最多向右匹配；最大值用"降序 a + lower_bound 前移找 b<a"求最多向左匹配。

### 算法流程

1. 读入 n、a、b（a、b 已递增，仍排序以防万一）。
2. **求 mn**：用 `multiset` 维护可用 b。按 a 升序，对每个 a 做 `lower_bound(a)`：
   - 若存在 b ≥ a，配对为向右，删除该 b；
   - 否则该 a 只能向左，`mn++`，删除最小 b。
3. **求 mx**：重建 `multiset`。按 a 降序，对每个 a 做 `lower_bound(a)` 再前移一位找最大 b < a：
   - 若存在，配对为向左，`mx++`，删除该 b；
   - 否则向右，删除最大 b。
4. 输出个数 k = mx - mn + 1，再输出 mn..mx 所有整数（空格分隔）。

### 复杂度分析

每个 a 一次 `multiset` 操作 O(log n)，共 n 个。总体 O(n log n)，对 n ≤ 200000 可行。

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    // Min left-movers: greedy, match smallest b >= a
    {
        multiset<int> bs(b.begin(), b.end());
        int mn = 0;
        for (int i = 0; i < n; i++) {
            auto it = bs.lower_bound(a[i]);
            if (it != bs.end()) { bs.erase(it); }
            else { bs.erase(bs.begin()); mn++; }
        }
        // Max left-movers: match largest b < a
        bs = multiset<int>(b.begin(), b.end());
        int mx = 0;
        for (int i = n - 1; i >= 0; i--) {
            auto it = bs.lower_bound(a[i]);
            if (it != bs.begin()) { --it; bs.erase(it); mx++; }
            else { bs.erase(prev(bs.end())); }
        }
        cout << (mx - mn + 1) << "\n";
        for (int v = mn; v <= mx; v++) cout << v << (v < mx ? " " : "\n");
    }
    return 0;
}
```
