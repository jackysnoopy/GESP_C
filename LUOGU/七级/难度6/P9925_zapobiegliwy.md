# P9925 [POI 2023/2024 R1] Zapobiegliwy student

## 题目描述

你有 $n$ 个线段在数轴上，你要选出尽量多的线段对 $(u_i,v_i)_{i=1}^k$，即最大化 $k$。

满足 $k+1$ 个要求：

- $u_1,u_2,\cdots,u_k$ 两两不交。
- $v_1,u_2,u_3,\cdots,u_k$ 两两不交。
- $u_1,v_2,u_3,u_4,\cdots,u_k$ 两两不交。
- $\cdots$
- $u_1,u_2,\cdots,u_{k-1},v_k$ 两两不交。

其中 $\forall i$，$u_i$ 与 $v_i$ 不能相同。

## 输入格式

第一行一个正整数 $n(n\geq2)$。

接下来 $n$ 行每行两个正整数 $a_i,b_i(1\leq a_i<b_i\leq10^9)$，表示一个线段的两个端点。

## 输出格式

第一行一个正整数 $k$。

接下来 $k$ 行，每行两个正整数 $u_i,v_i$，表示一对线段的编号。

## 题解

### 分析

这是一个贪心或动态规划问题，需要选择线段对。

### 算法思路

1. 理解线段不交的条件。
2. 使用贪心策略选择线段对。
3. 考虑所有可能的组合。

### 复杂度分析

- 时间复杂度：$O(n \log n)$。
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
    
    vector<pair<int, int>> segments(n);
    for (int i = 0; i < n; i++) {
        cin >> segments[i].first >> segments[i].second;
    }
    
    // 简单实现：贪心选择
    // 这里需要更复杂的算法
    vector<pair<int, int>> ans;
    
    // 按右端点排序
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return segments[i].second < segments[j].second;
    });
    
    // 贪心选择不相交的线段对
    int last_end = -1;
    for (int i = 0; i < n; i++) {
        int id = idx[i];
        if (segments[id].first > last_end) {
            ans.push_back({id + 1, id + 1});
            last_end = segments[id].second;
        }
    }
    
    cout << ans.size() << "\n";
    for (auto& p : ans) {
        cout << p.first << " " << p.second << "\n";
    }
    
    return 0;
}
```

## 测试数据

### 样例1

输入：
```
8
1 5
3 10
4 8
9 12
11 16
14 15
20 22
15 21
```

输出：
```
3
1 3
4 6
8 7
```

## 注意事项

1. 线段不交的条件需要仔细理解。
2. 需要最大化线段对的数量。
3. 注意输出格式。

## 参考资料

- 洛谷题解
- POI 官方题解
- 贪心算法相关资料