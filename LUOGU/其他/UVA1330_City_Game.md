# City Game

## 题目描述
[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4076

[PDF](https://uva.onlinejudge.org/external/13/p1330.pdf)

## 输入格式


## 输出格式


## 样例
### 样例 1
```
3
3 3
R R F
F F F
F R F

5 6
R F F F F F
F R F F F F
F F R F F F
F F F R F F
F F F F R R

4 5
R R R R R
R R F R R
R R R R R
R R F R R
```
```
9
27
3
```

## 解题思路
### 问题分析
01矩阵中找全部由 1 组成的最大矩形面积。

### 核心思路
对每行统计以该行为底的柱状图高度，每行用单调栈求最大矩形面积。

### 算法流程
1. 读入矩阵
2. 维护每列当前高度
3. 对每行用单调栈求最大矩形
4. 更新全局最大

### 复杂度分析
- 时间复杂度：O(nm)
- 空间复杂度：O(m)

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
    
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<int> h(m + 2, 0);
        int ans = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= m; j++) {
                char c; cin >> c;
                if (c == 'F') h[j]++;
                else h[j] = 0;
            }
            
            stack<int> st;
            st.push(0);
            for (int j = 1; j <= m + 1; j++) {
                while (h[j] < h[st.top()]) {
                    int height = h[st.top()]; st.pop();
                    ans = max(ans, height * (j - st.top() - 1));
                }
                st.push(j);
            }
        }
        
        cout << ans * 3 << "\n";
    }
    return 0;
}
```
