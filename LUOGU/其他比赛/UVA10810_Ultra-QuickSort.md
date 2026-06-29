# Ultra-QuickSort

## 题目描述

给定一个由 1 到 n 的整数组成的排列，求将其通过交换相邻元素排序为升序所需的最小交换次数。

## 输入格式

- 多组测试数据，每组第一行一个整数 n（0 表示结束）
- 接下来 n 行，每行一个整数

## 输出格式

每组数据输出一个整数，表示最小交换次数

## 样例

```
输入：
5
5
1
2
3
4
0

输出：
10
```

## 提示

- 相邻交换排序的最小次数等于逆序对数
- 使用归并排序可以在 O(n log n) 时间内统计逆序对

## 解题思路

### 问题分析

将序列排序为升序所需的最小相邻交换次数，恰好等于序列中逆序对的数量。

### 核心思路

使用归并排序在分治过程中统计逆序对。当右半部分的元素先于左半部分的元素被放入临时数组时，说明产生了逆序对，逆序对数量为左半部分剩余元素个数。

### 算法流程

1. 将序列分为左右两半
2. 递归统计左半部分和右半部分内部的逆序对
3. 在合并过程中，当右半部分的元素 a[j] < 左半部分的元素 a[i] 时：
   - 逆序对数 += mid - i + 1
4. 返回总的逆序对数

### 复杂度分析

- 时间复杂度：O(n log n)
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

long long merge_sort(vector<int>& a, int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) / 2;
    long long ans = merge_sort(a, l, mid) + merge_sort(a, mid + 1, r);
    
    vector<int> tmp;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp.push_back(a[i++]);
        else {
            tmp.push_back(a[j++]);
            ans += mid - i + 1;
        }
    }
    while (i <= mid) tmp.push_back(a[i++]);
    while (j <= r) tmp.push_back(a[j++]);
    for (int k = 0; k < (int)tmp.size(); k++)
        a[l + k] = tmp[k];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        int N;
        cin >> N;
        if (N == 0) break;
        vector<int> a(N);
        for (int i = 0; i < N; i++) cin >> a[i];
        cout << merge_sort(a, 0, N - 1) << "\n";
    }
    
    return 0;
}
```
