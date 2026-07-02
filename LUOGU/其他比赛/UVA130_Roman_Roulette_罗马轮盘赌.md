# UVA130 - Roman Roulette (罗马轮盘赌)

## 题目描述

罗马轮盘赌是一个约瑟夫问题的变种。n个人围成一圈，从位置1开始，顺时针数k个人，移除第k个人。然后，执行移除操作的人（即被移除者的下一个）也被移除。重复这个过程直到只剩一个人。

## 算法思路

1. 使用vector模拟圆圈中的人
2. 从位置0开始，每次找到要移除的位置
3. 移除该位置的人后，下一个位置的人也被移除
4. 如果只剩一人，游戏结束
5. 继续直到只剩一人

## 复杂度分析

- 时间复杂度：O(n²)，每次移除需要O(n)时间
- 空间复杂度：O(n)，存储人的列表

## C++ 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    while (cin >> n >> k && (n || k)) {
        vector<int> v(n);
        for (int i = 0; i < n; i++) v[i] = i + 1;
        int pos = 0;
        while (v.size() > 1) {
            int kill = (pos + k - 1) % v.size();
            v.erase(v.begin() + kill);
            if (v.size() > 1) {
                int killer = kill % v.size();
                v.erase(v.begin() + killer);
            }
            pos = kill % v.size();
        }
        cout << v[0] << endl;
    }
    return 0;
}
```

## 样例输入输出

输入：
```
10 3
10 5
0 0
```

输出：
```
4
8
```

解释：对于n=10, k=3的情况，模拟移除过程，最后剩下的人的位置是4。
