# [USACO06OPEN] The Milk Queue G

## 题目描述
N头奶牛挤奶，分两道工序。FJ做第一道，Rob做第二道。如果牛i先开始第一道，也先开始第二道。求最短总时间。

## 输入格式
第一行N，接下来N行每行A_i B_i。

## 输出格式
最短时间。

## 样例
输入：
```
3
2 2
7 4
3 5
```
输出：
```
16
```

## 解题思路

### 问题分析
- 经典流水线调度问题
- Johnson法则：按A_i+B_i降序排列

### 核心思路
- 按A_i+B_i降序排列
- 总时间=sum(A_i)+最后一头牛的B_i

### 复杂度分析
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Cow {
    int a, b;
    bool operator<(const Cow& o) const {
        return a + b > o.a + o.b;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<Cow> cows(n);
    for (int i = 0; i < n; i++) cin >> cows[i].a >> cows[i].b;
    
    sort(cows.begin(), cows.end());
    
    long long totalA = 0;
    for (int i = 0; i < n; i++) totalA += cows[i].a;
    
    long long maxB = 0;
    long long curB = 0;
    for (int i = 0; i < n; i++) {
        curB += cows[i].b;
        if (curB > maxB) maxB = curB;
    }
    
    cout << totalA + maxB << "\n";
    return 0;
}
```
