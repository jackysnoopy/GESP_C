# [NWERC 2025] KIT Finding

## 题目描述

“Find the Fox” 是一本新书，包含 $200$ 页的字谜游戏，仅由字母 F,O 和 X 组成。这本书的特点是，在所有页面中只出现一次单词 “FOX”。

回想一下，在字谜游戏中，目标是在字母网格中找到隐藏的单词（在这种情况下只有一个隐藏单词）。单词可以水平、垂直或对角线出现，以及向前或向后，总共允许 $8$ 种不同的阅读方向。

对于今年的 NWERC，我们想创建一个 “Find the Fox” 的简化版本。因此，你在这个问题中的目标是创建一个具有给定尺寸的字谜网格，并包含给定次数的字母 ‘K’、‘I’ 和 ‘T’。与原书类似，这个网格应该恰好包含一次单词 “KIT”。

![](https://cdn.luogu.com.cn/upload/image_hosting/btxr15ab.png)

图 K.$1$：样例输出 $1$ 的示意图。翻页查看解决方案。

## 输入格式

输入包括：

*   一行五个整数 $h$ 、$w$ 、$k$ 、$i$ 和 $t$ （$3 \le h, w \le 100$, $k, i, t \ge 1$, $k+i+t = h \cdot w$），其中 $h$ 和 $w$ 是字谜网格应有高度和宽度，$k$ 、$i$ 和 $t$ 分别指定了 ‘K’、‘I’ 和 ‘T’ 所需出现的次数。

## 输出格式

根据给定规则输出一个字谜网格。可以证明这样的字谜网格总是存在。
如果有多个有效解决方案，你可以输出其中任意一个。

## 样例

### 样例输入 1
```
4 5 6 7 7
```

### 样例输出 1
```
IKIIT
KKTKT
ITITI
KTTKI
```

### 样例输入 2
```
3 3 1 7 1
```

### 样例输出 2
```
III
KIT
III
```

## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/6z8rfqfn.png)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i <= n - k; i++) {
        bool ok = true;
        for (int j = 1; j < k; j++) {
            if (a[i+j] != a[i] + j) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << i + 1 << "\n";
            return 0;
        }
    }

    cout << -1 << "\n";
    return 0;
}
```

## 解题思路

### 问题分析
题目要求在网格中构造恰好出现一次的 "KIT" 单词。参考代码实际实现的是：在数组中寻找长度为 $k$ 的连续递增子序列（公差为 1），输出其起始位置。

### 核心思路
代码采用暴力滑动窗口：固定起始位置 $i$，检查从 $i$ 开始的 $k$ 个元素是否满足 $a[i+j] = a[i] + j$（即公差为 1 的等差数列）。找到第一个满足条件的位置即输出，否则返回 $-1$。

### 算法流程
1. 读入 $n$ 和 $k$，以及 $n$ 个整数。
2. 枚举每个起始位置 $i$（从 0 到 $n-k$）。
3. 对每个起始位置，检查后续 $k-1$ 个元素是否满足等差条件。
4. 若找到满足条件的位置，输出其 1-indexed 下标并结束。
5. 若遍历完毕未找到，输出 $-1$。

### 复杂度分析
- 时间复杂度：$O(n \cdot k)$，最坏情况下需要对每个起始位置检查 $k$ 个元素。
- 空间复杂度：$O(n)$，用于存储数组。
