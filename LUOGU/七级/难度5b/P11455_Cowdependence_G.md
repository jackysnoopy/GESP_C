# [USACO24DEC] Cowdependence G

## 题目描述
Farmer John 的 $N$ 头奶牛排成一行，第 $i$ 头奶牛标号为 $a_i$。具有相同标号且两两距离在 $x$ 以内的奶牛可以组成友谊小组。每头奶牛恰好属于一个小组。对于 $x=1$ 到 $N$，求最小小组数。

## 输入格式
第一行 $N$，第二行 $a_1 \dots a_N$。

## 输出格式
$N$ 行，第 $i$ 行为 $x=i$ 时的答案。

## 样例
输入：
```
9
1 1 1 9 2 1 2 1 1
```
输出：
```
7
5
4
4
4
4
4
3
3
```

## 提示
$1 \le N \le 10^5$，$1 \le a_i \le N$。

## 解题思路

### 问题分析
对于每个标号，其出现位置 $p_1 < p_2 < \dots < p_k$ 需要被分成若干组，使得同组内任意两点距离 $\le x$。贪心地，从左到右扫描，当当前位置与组起点距离 $> x$ 时开新组。一个标号所需组数 = $1 + $ 相邻出现位置间距 $> x$ 的对数。

### 核心思路
总组数 = 不同标号数 + 所有标号中相邻间距 $> x$ 的对数。预处理所有相邻间距并排序，对每个 $x$ 用二分查找快速计算。

### 算法流程
1. 收集每个标号的所有出现位置
2. 计算每个标号相邻出现位置的间距，存入数组
3. 排间距数组
4. 对每个 $x$，二分查找间距 $> x$ 的数量，加到标号数上输出

### 复杂度分析
- 时间：$O(N \log N)$
- 空间：$O(N)$

## 参考代码
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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> occ(n + 1);
    for (int i = 0; i < n; i++) {
        occ[a[i]].push_back(i);
    }
    vector<int> gaps;
    int numLabels = 0;
    for (int label = 1; label <= n; label++) {
        if (occ[label].empty()) continue;
        numLabels++;
        for (int j = 1; j < (int)occ[label].size(); j++) {
            gaps.push_back(occ[label][j] - occ[label][j - 1]);
        }
    }
    sort(gaps.begin(), gaps.end());
    for (int x = 1; x <= n; x++) {
        int g = (int)(gaps.end() - upper_bound(gaps.begin(), gaps.end(), x));
        cout << numLabels + g << "\n";
    }
    return 0;
}
```
