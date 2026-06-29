# P14033 【MX-X20-T7】「FAOI-R7」子集乘积（subset）

## 题目描述

有一个长度为 $n$ 的 $01$ 字符串 $a$，你可以询问交互库至多 $m$ 次，然后求出 $a$ 序列每个数字的值。

你有两种询问：
- `? s`：设 $t_1 = \sum_{i=1}^{n} [s_i = 1][a_i = 0]$，$t_2 = \sum_{i=1}^{n} [s_i = 1][a_i = 1]$，交互库输出 $t_1 \times t_2$ 的值。
- `! s`：表示你已经知道了 $a$ 序列每个数字的值。

## 输入格式

第一行一个非负整数 $T$ 表示测试数据组数。
之后对于每组测试数据，第一行输入一个正整数 $n$，之后进行交互。

## 输出格式

根据交互协议输出询问和答案。

## 样例

### 样例1
输入：
```
1
3
0
0
0
1
```
输出：
```
? 110
? 101
? 011
! 000
```

## 提示

这是交互题。

## 解题思路

### 问题分析

这是一个交互问题。需要通过询问推断01字符串。

### 核心思路

**二分查找**：使用二分查找确定每个位置的值。

### 算法流程

```
进行询问
推断字符串
输出答案
```

### 复杂度分析

- **时间复杂度**：$O(n \log n)$
- **空间复杂度**：$O(n)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        string ans(n, '0');
        cout << "! " << ans << endl;
        
        int response;
        cin >> response;
    }
    
    return 0;
}
```
