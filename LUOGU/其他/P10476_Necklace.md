# Necklace

## 题目描述
有一天，袁同学借了一条价值连城宝石项链，但是，一个严重的问题是，他竟然忘记了项链的主人是谁！在得知此事后，很多人向同学发来了很多邮件，都说项链是自己的，要求他归还（显然其中最多只有一个人说了真话）。袁同学要求每个人都写了一段关于自己项链的描述：

项链上的宝石用数字 $0$ 至 $9$ 来表示。一个对于项链的表示就是从项链的某个宝石开始：顺指针绕一圈，沿途记下经过的宝石，比如如下项链：

![](https://cdn.luogu.com.cn/upload/image_hosting/57501u19.png)

它的可能的四种表示是 $0123$、$1230$、$2301$、$3012$。

袁同学现在心急如焚，于是他找到了你，希望你能够编一个程序，判断两个给定的描述是否代表同一个项链（注意，项链是不会翻转的）。

## 输入格式
输入文件只有两行，每行一个由 $0$ 至 $9$ 组成的字符串，描述一个项链的表示（保证项链的长度是相等的）。

## 输出格式
如果两条项链不可能同构，那么输出 `No`，否则的话，第一行输出一个 `Yes` 第二行输出该项链的字典序最小的表示。

## 样例
### 样例 1
```
2234342423 
2423223434
```
```
Yes
2234342423
```

## 提示
设 $L =$ 项链长度，则 $1\leq L \leq 1000000$。

## 解题思路
### 问题描述
……
### 解题思路

### 问题分析
判断字符串是否循环同构（旋转后相同），并求最小表示。

### 核心思路
最小表示法。对字符串旋转后的所有表示中取字典序最小的。

### 算法流程
1. 读入字符串
2. 用双指针求最小表示
3. 判断两个字符串是否循环同构

### 复杂度分析
- 时间复杂度：O(n)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <string>
using namespace std;

int min_rep(const string& s) {
    int n = s.size(), i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        int diff = s[(i+k)%n] - s[(j+k)%n];
        if (diff == 0) k++;
        else {
            if (diff > 0) i += k + 1;
            else j += k + 1;
            if (i == j) j++;
            k = 0;
        }
    }
    return min(i, j);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string a, b;
    while (cin >> a >> b) {
        if (a.size() != b.size()) { cout << "No\n"; continue; }
        int pa = min_rep(a), pb = min_rep(b);
        int n = a.size();
        bool same = true;
        for (int i = 0; i < n; i++)
            if (a[(pa+i)%n] != b[(pb+i)%n]) { same = false; break; }
        cout << (same ? "Yes" : "No") << "\n";
    }
    return 0;
}
```
