# Number Base Conversion

## 题目描述
Write a program to convert numbers in one base to numbers in a second base. There are $62$ different digits:

$\{ 0\sim 9, A\sim Z,a\sim z \}$

HINT: If you make a sequence of base conversions using the output of one conversion as the input to the next, when you get back to the original base, you should get the original number.

## 输入格式
The first line of input contains a single positive integer. This is the number of lines that follow. Each of the following lines will have a (decimal) input base followed by a (decimal) output base followed by a number expressed in the input base. Both the input base and the output base will be in the range from $2$ to $62$. That is (in decimal) $A = 10, B = 11, \dots, Z = 35, a = 36, b = 37, \dots, z = 61$ ($0\sim 9$ have their usual meanings).

## 输出格式
The output of the program should consist of three lines of output for each base conversion performed. The first line should be the input base in decimal followed by a space then the input number (as given expressed in the input base). The second output line should be the output base followed by a space then the input number (as expressed in the output base). The third output line is blank.

## 样例
### 样例 1
```
8
62 2 abcdefghiz
10 16 1234567890123456789012345678901234567890
16 35 3A0C92075C0DBF3B8ACBC5F96CE3F0AD2
35 23 333YMHOUE8JPLT7OX6K9FYCQ8A
23 49 946B9AA02MI37E3D3MMJ4G7BL2F05
49 61 1VbDkSIMJL3JjRgAdlUfcaWj
61 5 dl9MDSWqwHjDnToKcsWE1S
5 10 42104444441001414401221302402201233340311104212022133030
```
```
62 abcdefghiz
2 11011100000100010111110010010110011111001001100011010010001

10 1234567890123456789012345678901234567890
16 3A0C92075C0DBF3B8ACBC5F96CE3F0AD2

16 3A0C92075C0DBF3B8ACBC5F96CE3F0AD2
35 333YMHOUE8JPLT7OX6K9FYCQ8A

35 333YMHOUE8JPLT7OX6K9FYCQ8A
23 946B9AA02MI37E3D3MMJ4G7BL2F05

23 946B9AA02MI37E3D3MMJ4G7BL2F05
49 1VbDkSIMJL3JjRgAdlUfcaWj

49 1VbDkSIMJL3JjRgAdlUfcaWj
61 dl9MDSWqwHjDnToKcsWE1S

61 dl9MDSWqwHjDnToKcsWE1S
5 42104444441001414401221302402201233340311104212022133030

5 42104444441001414401221302402201233340311104212022133030
10 1234567890123456789012345678901234567890
```

## 提示
题目保证 $1\le T\le 100$，要转换的数字是不超过 $10^{110}$ 的自然数。

## 解题思路
### 问题分析
将数字从 a 进制转换为 b 进制。数字用 0-9, A-Z, a-z 表示（共 62 个字符）。

### 核心思路
先转为十进制（高精度），再转为目标进制。因为数字可能很大，直接用 Python 思想：用字符串处理。

### 算法流程
1. 读入 a, b 和数字串 s
2. 将 s 从 a 进制转为十进制大数
3. 再转为 b 进制
4. 输出结果

### 复杂度分析
- 时间复杂度：O(n²)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int char_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return c - 'a' + 36;
}

char val_char(int v) {
    if (v < 10) return '0' + v;
    if (v < 36) return 'A' + v - 10;
    return 'a' + v - 36;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int a, b;
        string s;
        cin >> a >> b >> s;
        
        vector<int> num;
        for (char c : s) num.push_back(char_val(c));
        
        vector<int> res;
        while (!num.empty()) {
            int carry = 0;
            vector<int> next;
            for (int v : num) {
                carry = carry * a + v;
                if (carry >= b || !next.empty()) {
                    next.push_back(carry / b);
                    carry %= b;
                }
            }
            res.push_back(carry);
            num = next;
        }
        
        reverse(res.begin(), res.end());
        cout << a << " " << s << "\n";
        cout << b << " ";
        for (int v : res) cout << val_char(v);
        cout << "\n\n";
    }
    return 0;
}
```
