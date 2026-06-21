# HISTOGRA - Largest Rectangle in a Histogram

## 题目描述
A histogram is a polygon composed of a sequence of rectangles aligned at a common base line. The rectangles have equal widths but may have different heights. For example, the figure on the left shows the histogram that consists of rectangles with the heights 2, 1, 4, 5, 1, 3, 3, measured in units where 1 is the width of the rectangles:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP1805/b9567e3483620f1fe679470ac44083eae9842e79.png) Usually, histograms are used to represent discrete distributions, e.g., the frequencies of characters in texts. Note that the order of the rectangles, i.e., their heights, is important. Calculate the area of the largest rectangle in a histogram that is aligned at the common base line, too. The figure on the right shows the largest aligned rectangle for the depicted histogram.

## 输入格式


## 输出格式


## 样例
### 样例 1
```
7 2 1 4 5 1 3 3
4 1000 1000 1000 1000
0
```
```
8
4000
```

## 解题思路
### 问题分析
直方图中最大矩形面积。

### 核心思路
单调栈。对每个柱找左右第一个比它矮的柱，面积 = 高 × (右-左-1)。

### 算法流程
1. 读入 n 和高度
2. 单调递增栈，当 a[i] < a[栈顶] 时弹栈计算面积
3. 最后处理剩余
4. 输出最大面积

### 复杂度分析
- 时间复杂度：O(n)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        int n; cin >> n;
        if (n == 0) break;
        vector<long long> h(n + 2, 0);
        for (int i = 1; i <= n; i++) cin >> h[i];
        
        stack<int> st;
        st.push(0);
        long long ans = 0;
        for (int i = 1; i <= n + 1; i++) {
            while (h[i] < h[st.top()]) {
                long long height = h[st.top()]; st.pop();
                long long width = i - st.top() - 1;
                ans = max(ans, height * width);
            }
            st.push(i);
        }
        cout << ans << "\n";
    }
    return 0;
}
```
