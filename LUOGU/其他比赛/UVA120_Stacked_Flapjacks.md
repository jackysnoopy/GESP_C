# UVA120 - Stacked Flapjacks (堆叠煎饼)

## 题目描述

给定一叠不同大小的煎饼，只能使用一种操作：将铲子插入任意位置，然后将该位置上方的所有煎饼翻转。目标是通过一系列翻转操作，将煎饼从上到下按从小到大排序。

## 输入格式

每行包含若干个空格分隔的整数，表示煎饼的大小（从上到下）。

## 输出格式

第一行输出原始的煎饼堆叠顺序。
第二行输出翻转操作的位置序列（从底部数起），以空格分隔，最后以 0 结尾。

## 样例

输入：
```
1 5 4 2 3
5 1 2 3 4
```

输出：
```
1 5 4 2 3
2 4 5 4 2 0
5 1 2 3 4
2 5 3 2 0
```

## 解题思路

### 问题分析

这是一个经典的排序问题，但只能使用特定的翻转操作。每次翻转操作会将铲子位置上方的所有元素反转。

### 核心思路

使用选择排序的思想：
1. 从未排序部分找到最大的煎饼
2. 如果它不在顶部，先翻转到顶部
3. 然后翻转到正确的位置

### 算法流程

1. 从最后一个位置开始向前处理
2. 对于每个位置，找到未排序部分中的最大值
3. 如果最大值不在当前处理的位置，执行两次翻转：
   - 第一次将最大值翻转到顶部
   - 第二次将最大值翻转到目标位置
4. 记录每次翻转的位置（从底部数，1-indexed）

### 复杂度分析

- 时间复杂度：O(n²)，其中 n 是煎饼数量
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void flip(vector<int>& pancakes, int pos) {
    int left = 0, right = pos;
    while (left < right) {
        swap(pancakes[left], pancakes[right]);
        left++;
        right--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;

        vector<int> pancakes;
        int num = 0;
        bool inNumber = false;

        for (char c : line) {
            if (c == ' ') {
                if (inNumber) {
                    pancakes.push_back(num);
                    num = 0;
                    inNumber = false;
                }
            } else {
                num = num * 10 + (c - '0');
                inNumber = true;
            }
        }
        if (inNumber) pancakes.push_back(num);

        int n = pancakes.size();
        
        for (int i = 0; i < n; i++) {
            cout << pancakes[i];
            if (i < n - 1) cout << " ";
        }
        cout << "\n";

        vector<int> flips;

        for (int target = 0; target < n; target++) {
            int maxIdx = target;
            for (int i = target; i < n; i++) {
                if (pancakes[i] > pancakes[maxIdx]) {
                    maxIdx = i;
                }
            }

            if (maxIdx == target) continue;

            if (maxIdx != n - 1) {
                flip(pancakes, maxIdx);
                flips.push_back(n - maxIdx);
            }

            flip(pancakes, n - target - 1);
            flips.push_back(n - target);
        }

        flips.push_back(0);

        for (int i = 0; i < (int)flips.size(); i++) {
            cout << flips[i];
            if (i < (int)flips.size() - 1) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
```
