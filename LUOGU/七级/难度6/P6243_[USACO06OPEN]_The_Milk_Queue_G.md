# [USACO06OPEN] The Milk Queue G

## 题目描述

每早，FJ 的 N 头奶牛都排成一列挤奶，一个个进到仓库。为提高速率，FJ 把整个挤奶过程划分成两道工序：FJ 负责第一道，Rob 负责第二道。如果某头牛先于另一头牛开始第一道工序，那么她同样先开始第二道工序。

请计算按最优方式排队后最少需要多少时间才能挤完奶。对于每头奶牛，数据提供第一道工序的时间 A_i 和第二道工序的时间 B_i。

## 输入格式

第一行一个整数 N。
接下来 N 行，每行两个整数表示第 i 头牛的 A_i, B_i 值。

## 输出格式

输出按最优方案排队后挤奶所需的最短时间。

## 样例

**输入：**
```
3
2 2
7 4
3 5
```

**输出：**
```
16
```

## 提示

把奶牛们按照 3，1，2 的顺序排队，这样挤奶总共花费 16 个单位时间。

- 1 ≤ N ≤ 25000
- 1 ≤ A_i, B_i ≤ 2×10^4

## 解题思路

### 问题分析

这是一个经典的两台机器流水车间调度问题（2-machine flow shop scheduling）。有 N 个工件，每个工件需要先在机器 1 上加工（耗时 A_i），再在机器 2 上加工（耗时 B_i）。机器 1 按顺序处理所有工件，机器 2 也按同样顺序处理，但机器 2 必须等工件在机器 1 上完成且机器 2 空闲后才能开始。

### 核心思路

使用 **Johnson 法则**：按 A_i + B_i **升序**排列。

排序后，模拟两台机器的加工过程：
- 机器 1 按顺序处理每个工件，累积时间
- 机器 2 在工件完成机器 1 加工且机器 2 空闲后开始加工

总时间 = 机器 2 完成最后一个工件的时间。

### 算法流程

1. 读入 N 头牛的 A_i, B_i
2. 按 A_i + B_i 升序排序
3. 模拟两台机器的加工过程
4. 输出机器 2 完成所有工件的时间

### 复杂度分析

- 时间复杂度：O(N log N)（排序）
- 空间复杂度：O(N)

## 参考代码

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Cow {
    int a, b;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Cow> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i].a >> cows[i].b;
    }
    
    // Johnson's rule: sort by a+b ascending
    sort(cows.begin(), cows.end(), [](const Cow& x, const Cow& y) {
        return x.a + x.b < y.a + y.b;
    });
    
    // Simulate the flow shop
    long long c1 = 0, c2 = 0;
    for (int i = 0; i < n; i++) {
        c1 += cows[i].a;
        c2 = max(c2, c1) + cows[i].b;
    }
    
    cout << c2 << "\n";
    
    return 0;
}
```
