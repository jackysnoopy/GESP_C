# UVA136 - Ugly Numbers (丑数)

## 题目描述

丑数是只能被2、3、5整除的数。求第1500个丑数。

## 算法思路

1. 使用动态规划，维护三个指针分别指向乘以2、3、5的位置
2. 每次取三个候选值中的最小值作为下一个丑数
3. 更新对应指针，确保不重复

## 复杂度分析

- 时间复杂度：O(n)，线性扫描
- 空间复杂度：O(n)，存储所有丑数

## C++ 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    const int N = 1500;
    vector<long long> ugly(N);
    ugly[0] = 1;
    int i2 = 0, i3 = 0, i5 = 0;
    for (int i = 1; i < N; i++) {
        long long next2 = ugly[i2] * 2;
        long long next3 = ugly[i3] * 3;
        long long next5 = ugly[i5] * 5;
        long long next = min({next2, next3, next5});
        ugly[i] = next;
        if (next == next2) i2++;
        if (next == next3) i3++;
        if (next == next5) i5++;
    }
    cout << "The 1500'th ugly number is " << ugly[N - 1] << "." << endl;
    return 0;
}
```

## 样例输入输出

输入：无

输出：
```
The 1500'th ugly number is 859963392.
```

解释：第1500个丑数是859963392。
