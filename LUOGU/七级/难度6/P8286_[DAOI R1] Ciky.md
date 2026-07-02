# 「DAOI R1」Ciky

## 题目描述
深秋，落叶纷纷，瞳可开心了。

Augen 带着小朋友们一起在树林里捡了很多金黄的叶子。

他们捡的所有叶子都是正多边形，现在 Augen 准备把它们制作成标本装订成册送给瞳。

制作一个标本，需要沿一片叶子的边缘画上颜色，每一片叶子边缘的颜色不能相同。同时，每一个标本都有相对应的美丽程度。

将标本装订成册时，需满足以下条件：
- 第 $i$ 片叶子的周长不能大于第 $i+1$ 片叶子；
- 第 $i$ 片叶子的美丽程度不能大于第 $i+1$ 片叶子。

Augen 拥有 $n$ 支不同颜色的笔，每支还可以画 $a_i$ 的长度。

$m$ 片叶子，第 $i$ 片叶子为正 $k_i$ 边形，每条边长 $b_i$，每片叶子的美丽程度 $c_i$。

更简单地说，即，只有满足 $k_i*b_i \leq a_j$ 的情况下，可以用第 $j$ 支画笔，画第 $i$ 片叶子。

Augen 希望能更多的送出标本或者使得制作出来的标本美丽程度总和最大。

## 输入格式
第一行两个整数，$n,m$。

第二行共 $n$ 个整数，第 $i$ 个整数表示 $a_i$。

第三行共 $m$ 个整数，第 $i$ 个整数表示 $b_i$。

第四行共 $m$ 个整数，第 $i$ 个整数表示 $c_i$。

第五行共 $m$ 个整数，第 $i$ 个整数表示 $k_i$。

## 输出格式
共两行。

第一行，一个整数，表示册子中标本的个数的最大值。

第二行，一个整数，表示制作出来的标本美丽程度的最大值。

## 样例
### 样例1
输入:
```
5 3
9 7 2 5 6
1 2 1
2 6 8
3 3 4
```
输出:
```
3
16
```

## 提示
- 时间限制：1000ms
- 内存限制：131072KB

## 解题思路

### 问题分析
需要匹配画笔和叶子，使得：
1. 匹配数量最多
2. 美丽程度总和最大

### 核心思路
1. 贪心匹配：优先匹配周长小的叶子
2. 使用排序和双指针

### 算法流程
1. 计算每片叶子的周长
2. 对画笔和叶子排序
3. 贪心匹配

### 复杂度分析
- 时间复杂度：$O(n \log n + m \log m)$
- 空间复杂度：$O(n + m)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<long long> b(m), c(m), k(m);
    for (int i = 0; i < m; i++) cin >> b[i];
    for (int i = 0; i < m; i++) cin >> c[i];
    for (int i = 0; i < m; i++) cin >> k[i];
    
    vector<long long> perimeter(m);
    for (int i = 0; i < m; i++) {
        perimeter[i] = k[i] * b[i];
    }
    
    vector<long long> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    
    vector<pair<long long, long long>> leaves(m);
    for (int i = 0; i < m; i++) {
        leaves[i] = {perimeter[i], c[i]};
    }
    sort(leaves.begin(), leaves.end());
    
    int count = 0;
    int pen_idx = 0;
    
    for (int i = 0; i < m && pen_idx < n; i++) {
        while (pen_idx < n && sorted_a[pen_idx] < leaves[i].first) {
            pen_idx++;
        }
        if (pen_idx < n) {
            count++;
            pen_idx++;
        }
    }
    
    cout << count << endl;
    
    long long beauty = 0;
    vector<pair<long long, int>> leaves_with_idx(m);
    for (int i = 0; i < m; i++) {
        leaves_with_idx[i] = {perimeter[i], i};
    }
    sort(leaves_with_idx.begin(), leaves_with_idx.end());
    
    vector<bool> used(n, false);
    for (int i = 0; i < m; i++) {
        int leaf_idx = leaves_with_idx[i].second;
        for (int j = 0; j < n; j++) {
            if (!used[j] && a[j] >= perimeter[leaf_idx]) {
                used[j] = true;
                beauty += c[leaf_idx];
                break;
            }
        }
    }
    
    cout << beauty << endl;
    
    return 0;
}
```