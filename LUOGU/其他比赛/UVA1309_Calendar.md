# Calendar

## 题目描述

给定一个起始星期（0=Sunday, 1=Monday, ..., 6=Saturday）、年份和月份，输出该月的日历。日历以指定的星期为第一列。

## 输入格式

- 多组测试数据，每组三个整数 w, y, m，分别表示起始星期、年份、月份

## 输出格式

输出该月的日历，第一行为星期标题 "Sun Mon Tue Wed Thu Fri Sat"，之后每行最多 7 天，右对齐占 3 位。每组数据之间输出一个空行。

## 样例

```
输入：
6 2006 5
0 2006 5

输出：
Sun Mon Tue Wed Thu Fri Sat
    1   2   3   4   5   6 
 7   8   9  10  11  12  13 
14  15  16  17  18  19  20 
21  22  23  24  25  26  27 
28  29  30  31 

Sun Mon Tue Wed Thu Fri Sat
    1   2   3   4   5   6 
 7   8   9  10  11  12  13 
14  15  16  17  18  19  20 
21  22  23  24  25  26  27 
28  29  30  31 

```

## 提示

- 使用基姆拉尔森计算公式或蔡勒公式计算某天是星期几
- 注意闰年的判断

## 解题思路

### 问题分析

需要根据给定的年月和起始星期，生成该月的日历。

### 核心思路

1. 计算该月第一天是星期几
2. 根据起始星期计算起始偏移量
3. 逐日输出，注意对齐和换行

### 算法流程

1. 计算该月的天数 days（考虑闰年）
2. 计算该月第一天是星期几 dow
3. 计算起始偏移量 start = (dow - w) % 7
4. 输出星期标题
5. 输出 start 个空格
6. 逐日输出日期，每 7 天换行

### 复杂度分析

- 时间复杂度：O(1)
- 空间复杂度：O(1)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

static bool is_leap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

static int days_in_month(int y, int m) {
    static const int md[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && is_leap(y)) return 29;
    return md[m - 1];
}

static int day_of_week(int y, int m, int d) {
    int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    if (m < 3) --y;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int w, y, m;
    bool first = true;
    while (cin >> w >> y >> m) {
        if (!first) cout << '\n';
        first = false;
        int days = days_in_month(y, m);
        int dow = day_of_week(y, m, 1);
        int start = ((dow - w) % 7 + 7) % 7;

        cout << "Sun Mon Tue Wed Thu Fri Sat\n";
        for (int i = 0; i < start; ++i) cout << "    ";
        for (int d = 1; d <= days; ++d) {
            cout << setw(3) << d << ' ';
            if ((start + d) % 7 == 0) cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}
```
