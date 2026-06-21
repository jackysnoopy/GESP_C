# [NWERC 2003] Subway tree systems

## 题目描述
Some major cities have subway systems in the form of a tree, i.e. between any pair of stations, there is one and only one way of going by subway. Moreover, most of these cities have a unique central station. Imagine you are a tourist in one of these cities and you want to explore all of the subway system. You start at the central station and pick a subway line at random and jump aboard the subway car. Every time you arrive at a station, you pick one of the subway lines you have not yet travelled on. If there is none left to explore at your current station, you take the subway line back on which you first came to the station, until you eventually have travelled along all of the lines twice,once for each direction. At that point you are back at the central station. Afterwards, all you remember of the order of your exploration is whether you went further away from the central station or back towards it at any given time, i.e. you could encode your tour as a binary string, where 0 encodes taking a subway line getting you one station further away from the central station, and 1 encodes getting you one station closer to the central station.

![](https://cdn.luogu.com.cn/upload/image_hosting/57sf9gvq.png)

## 输入格式
On the first line of input is a single positive integer n, telling the number of test scenarios to follow.Each test scenario consists of two lines, each containing a string of the characters '0' and '1' of length at most 3000, both describing a correct exploration tour of a subway tree system.

## 输出格式
exploration tours of the same subway tree system, or the text "different" if the two strings cannot be exploration tours of the same subway tree system.

## 样例
### 样例 1
```
2
0010011101001011
0100011011001011
0100101100100111
0011000111010101
```
```
same
different
```

## 提示
None

## 解题思路
### 问题分析
判断两棵树的子树系统是否同构（树根为 0 点）。

### 核心思路
树的括号表示最小化。将子树递归排序后得到规范表示。

### 算法流程
1. 读入树的括号表示
2. 递归解析，对子树排序
3. 比较两棵树的规范表示

### 复杂度分析
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string parse(const string& s, int& pos) {
    vector<string> children;
    pos++; // skip '('
    while (s[pos] == '(')
        children.push_back(parse(s, pos));
    pos++; // skip ')'
    
    sort(children.begin(), children.end());
    string res = "(";
    for (const string& c : children) res += c;
    res += ")";
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; cin >> T;
    while (T--) {
        string a, b; cin >> a >> b;
        int pa = 0, pb = 0;
        string ra = parse(a, pa);
        string rb = parse(b, pb);
        cout << (ra == rb ? "same" : "different") << "\n";
    }
    return 0;
}
```
