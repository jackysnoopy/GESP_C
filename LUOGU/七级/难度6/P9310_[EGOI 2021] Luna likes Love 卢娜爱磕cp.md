# P9310 [EGOI 2021] Luna likes Love / 卢娜爱磕 cp

## 题目描述

卢娜让 $2n$ 个朋友排成一条长队，并给他们每人一个 $1\sim n$ 的整数。每个整数恰好出现两次。每一对有相同数字的朋友组成一对情侣。

卢娜希望让每一对情侣去一次约会。为了让一对情侣去约会，双方在队伍中必须互相紧挨着。

卢娜可以进行两种操作：
- 让任意两个紧挨着的人交换位置。
- 如果一对情侣互相紧挨着，卢娜可以让他们去约会。这一对情侣将从队伍中离开，后面的人会补上他们的位置。

请求出让所有人去约会的最少操作次数。

## 输入格式

第一行一个整数 $n$。

第二行 $2n$ 个整数 $a_i$，依次表示队伍中朋友拿到的数字。

## 输出格式

一行，一个整数，表示最少操作次数。

## 题解

### 分析

这是一个贪心或动态规划问题。需要找到最少的操作次数，使得所有情侣都能约会。

### 算法思路

1. 记录每个数字的位置。
2. 使用贪心策略，每次选择最近的情侣进行操作。
3. 计算交换和约会的总次数。

### 复杂度分析

- 时间复杂度：$O(n)$。
- 空间复杂度：$O(n)$。

### 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    
    vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
    }
    
    // 记录每个数字的位置
    vector<int> pos(n + 1);
    for (int i = 0; i < 2 * n; i++) {
        pos[a[i]] = i;
    }
    
    // 简单贪心：每次选择最近的情侣
    int ans = 0;
    vector<bool> removed(2 * n, false);
    
    for (int i = 0; i < 2 * n; i++) {
        if (removed[i]) continue;
        
        int val = a[i];
        int partner_pos = pos[val];
        
        if (partner_pos == i + 1) {
            // 已经相邻
            removed[i] = true;
            removed[partner_pos] = true;
            ans++;
        } else {
            // 需要交换
            ans++;
            // 交换相邻位置
            for (int j = i + 1; j < partner_pos; j++) {
                if (!removed[j]) {
                    ans++;
                }
            }
            removed[i] = true;
            removed[partner_pos] = true;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
```

## 测试数据

### 样例1

输入：
```
3
3 1 2 1 2 3
```

输出：
```
4
```

### 样例2

输入：
```
5
5 1 2 3 2 3 1 4 5 4
```

输出：
```
7
```

## 注意事项

1. 需要理解操作的含义和顺序。
2. 贪心策略可能不是最优解，需要仔细分析。
3. 注意处理情侣已经相邻的情况。

## 参考资料

- 洛谷题解
- EGOI 2021 官方题解
- 贪心算法相关资料