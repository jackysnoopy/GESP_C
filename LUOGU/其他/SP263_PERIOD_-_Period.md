# PERIOD - Period

## 题目描述
For each prefix of a given string **_S_** with **_N_** characters (each character has an ASCII code between 97 and 126, inclusive), we want to know whether the prefix is a periodic string. That is, for each **_i_** (2 <= **_i_**  <= **_N_**) we want to know the largest **_K_** > 1 (if there is one) such that the prefix of **_S_** with length **_i_** can be written as **_A_ $ ^{K} $** , that is **_A_** concatenated **_K_** times, for some string **_A_**. Of course, we also want to know the period **_K_**.

## 输入格式
The first line of the input file will contains only the number _T (1 <= T <= 10)_  of the test cases.

 Each test case consists of two lines. The first one contains **_N_** (2 <= **_N_** <= 1 000 000) – the size of the string **_S_**. The second line contains the string **_S_**.

## 输出格式
For each test case, output “Test case #” and the consecutive test case number on a single line; then, for each prefix with length **i** that has a period **K** > 1, output the prefix size **i** and the period **K** separated by a single space; the prefix sizes must be in increasing order. Print a blank line after each test case.

## 样例
### 样例 1
```
2
3
aaa
12
aabaabaabaab
```
```
Test case #1
2 2
3 3

Test case #2
2 2
6 2
9 3
12 4
```

## 解题思路
### 问题分析
对字符串每个前缀，求最小周期长度使周期串组成该前缀。

### 核心思路
KMP 的 next 数组。若前缀长度 i 能被 i - next[i] 整除，则存在周期。

### 算法流程
1. 读入 n 和字符串
2. 计算 next 数组
3. 对每个 i，若 i % (i-next[i]) == 0 且 i/(i-next[i])>1，输出

### 复杂度分析
- 时间复杂度：O(n)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; cin >> T;
    for (int cas = 1; cas <= T; cas++) {
        int n; string s;
        cin >> n >> s;
        
        vector<int> nxt(n+1, 0);
        for (int i = 2, j = 0; i <= n; i++) {
            while (j && s[i-1] != s[j]) j = nxt[j];
            if (s[i-1] == s[j]) j++;
            nxt[i] = j;
        }
        
        cout << "Test case #" << cas << "\n";
        for (int i = 2; i <= n; i++) {
            int p = i - nxt[i];
            if (i % p == 0 && i / p > 1)
                cout << i << " " << i / p << "\n";
        }
        cout << "\n";
    }
    return 0;
}
```
