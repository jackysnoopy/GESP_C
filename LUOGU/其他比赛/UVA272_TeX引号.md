# UVA272 - TeX Quotes (TeX引号)

## 题目描述

将文本中的普通引号转换为TeX格式的引号。

TeX中：
- 左引号用两个反引号表示：``
- 右引号用两个单引号表示：''

## 输入格式

- 多行文本，直到文件结束

## 输出格式

- 转换后的TeX格式文本

## 样例

### 输入
```
"To be or not to be," quoth the Bard, "that
is the question".
```

### 输出
```
``To be or not to be,'' quoth the Bard, ``that
is the question''.
```

## 提示

- 输入可能包含多行
- 引号总是成对出现
- 注意空格的处理

## 解题思路

### 问题分析

需要将普通引号转换为TeX格式的引号：
- 第一个引号（左引号）转换为 ``
- 第二个引号（右引号）转换为 ''

### 核心思路

1. 遍历每个字符
2. 遇到引号时，根据当前状态（左/右）决定输出
3. 交替切换状态

### 算法流程

1. 使用一个布尔变量标记当前是左引号还是右引号
2. 遇到引号时：
   - 如果是左引号，输出 ``
   - 如果是右引号，输出 ''
3. 切换状态

### 复杂度分析

- 时间复杂度：O(n)，n是文本长度
- 空间复杂度：O(1)

## 参考代码

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    bool left = true;
    while (getline(cin, line)) {
        string result = "";
        for (char c : line) {
            if (c == '"') {
                if (left) {
                    result += "``";
                } else {
                    result += "''";
                }
                left = !left;
            } else {
                result += c;
            }
        }
        cout << result << "\n";
    }
    return 0;
}
```
