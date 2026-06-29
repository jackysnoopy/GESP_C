# [SEERC 2003 / USACO5.5] 隐藏口令 Hidden Password

## 题目描述

有时候程序员有很奇怪的方法来隐藏他们的口令。Binny 会选择一个字符串 $S$（由 $N$ 个小写字母组成，$5 \le N \le 5 \times {10}^6$），然后他把 $S$ 顺时针绕成一个圈，每次取一个做开头字母并顺时针依次取字母而组成一个字符串。这样将得到一些字符串，他把它们排序后取出第一个字符串。把这个字符串的第一个字母在原字符串中的位置减 $1$ 做为口令。

如字符串 `alabala`，按操作的到 $7$ 个字符串，排序后得：

`aalabal`
`abalaal`  
`alaalab`  
`alabala`  
`balaala`  
`laalaba`  
`labalaa`

第一个字符串为 `aalabal`，这个 `a` 在原字符串位置为 $7$，$7-1=6$，则 $6$ 为口令。

## 输入格式

第一行：一个数：$N$

第二行开始：字符串：$S$（每 $72$ 个字符一个换行符）

## 输出格式

一行，为得到的口令

## 样例

Sample 1:
Input:
7
anabana
Output:
6

## 提示

测试数据题目满足：

$30 \%$ 的数据 $n \le {10}^4$。  
$70 \%$ 的数据 $n \le {10}^5$。  
$100 \%$ 的数据 $1 \le n \le 5 \times {10}^6$。

题目翻译来自 NOCOW。

USACO Training Section 5.5

// 20170523 新增数据四组

## 解题思路

### 问题分析
- 给定一个字符串 $S$，长度为 $N$（$5 \le N \le 5 \times 10^6$），将其视为一个环。
- 对于每个起始位置 $i$（$0 \le i < N$），从该位置开始顺时针读取 $N$ 个字符，得到一个字符串 $T_i$。
- 将所有 $T_i$ 按字典序排序，取最小的那个字符串 $T_{min}$。
- 输出 $T_{min}$ 在原字符串 $S$ 中的起始位置（从 $0$ 开始计数）。

### 核心思路
- 该问题等价于寻找字符串 $S$ 的最小表示法。
- 最小表示法是字符串 $S$ 的所有循环移位中字典序最小的那个移位的起始位置。
- 可以使用双指针法在 $O(N)$ 时间内解决。

### 算法流程
1. 初始化两个指针 $i = 0$ 和 $j = 1$，以及当前匹配长度 $k = 0$。
2. 比较 $S[(i+k) \% N]$ 和 $S[(j+k) \% N]$：
   - 如果相等，则 $k$ 增加 1。
   - 如果不相等：
     - 如果 $S[(i+k) \% N] > S[(j+k) \% N]$，则 $i = i + k + 1$。
     - 否则，$j = j + k + 1$。
     - 如果 $i == j$，则 $j$ 增加 1。
     - 重置 $k = 0$。
3. 重复步骤 2 直到 $i$ 或 $j$ 超过 $N$。
4. 输出 $\min(i, j)$。

### 复杂度分析
- 时间复杂度：$O(N)$，每个字符最多被比较两次。
- 空间复杂度：$O(N)$，存储字符串。

## 参考代码

```cpp

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    string s;
    cin >> n >> s;
    
    // 最小表示法
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        char a = s[(i + k) % n];
        char b = s[(j + k) % n];
        if (a == b) {
            k++;
        } else {
            if (a > b) {
                i = i + k + 1;
            } else {
                j = j + k + 1;
            }
            if (i == j) {
                j++;
            }
            k = 0;
        }
    }
    
    cout << min(i, j) << "\n";
    return 0;
}

```
