# [CCC 2007] Snowflake Snow Snowflakes

## 题目描述
You may have heard that no two snowflakes are alike. Your task is to write a program to determine whether this is really true. Your program will read information about a collection of snowflakes, and search for a pair that may be identical. Each snowflake has six arms. For each snowflake, your program will be provided with a measurement of the length of each of the six arms. Any pair of snowflakes which have the same lengths of corresponding arms should be flagged by your program as possibly identical.

## 输入格式
The first line of input will contain a single integer $n$, $0 < n \le 100000$ , the number of snowflakes to follow. This will be followed by $n$ lines, each describing a snowflake. Each snowflake will be described by a line containing six integers (each integer is at least $0$ and less than $10000000$) , the lengths of the arms of the snow ake. The lengths of the arms will be given in order around the snowflake (either clockwise or counterclockwise), but they may begin with any of the six arms. For example, the same snowflake could be described as $1 2 3 4 5 6$ or $4 3 2 1 6 5$ .

## 输出格式
If all of the snowflakes are distinct, your program should print the message:

`No two snowflakes are alike.`

If there is a pair of possibly identical snow akes, your program should print the message:

`Twin snowflakes found.`

## 样例
### 样例 1
```
2 
1 2 3 4 5 6 
4 3 2 1 6 5
```
```
Twin snowflakes found.
```

## 解题思路
### 问题分析
判断两片雪花是否相同（可旋转、翻转）。每片雪花 6 个角。

### 核心思路
对每片雪花求最小表示（12 种排列中字典序最小的）。

### 算法流程
1. 读入 n 和雪花
2. 对每片计算最小表示
3. 排序后检查是否有相同
4. 输出

### 复杂度分析
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> min_rep(const vector<int>& a) {
    vector<int> b(2 * 6);
    for (int i = 0; i < 6; i++) b[i] = b[i+6] = a[i];
    
    vector<int> best(6);
    // 顺时针
    for (int s = 0; s < 6; s++) {
        vector<int> cur(6);
        for (int i = 0; i < 6; i++) cur[i] = b[s+i];
        if (s == 0 || cur < best) best = cur;
    }
    // 逆时针
    reverse(b.begin(), b.end());
    for (int s = 0; s < 6; s++) {
        vector<int> cur(6);
        for (int i = 0; i < 6; i++) cur[i] = b[s+i];
        if (cur < best) best = cur;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<vector<int>> snowflakes;
    for (int i = 0; i < n; i++) {
        vector<int> a(6);
        for (int j = 0; j < 6; j++) cin >> a[j];
        snowflakes.push_back(min_rep(a));
    }
    
    sort(snowflakes.begin(), snowflakes.end());
    for (int i = 1; i < n; i++) {
        if (snowflakes[i] == snowflakes[i-1]) {
            cout << "Twin snowflakes found.\n";
            return 0;
        }
    }
    cout << "No two snowflakes are alike.\n";
    return 0;
}
```
