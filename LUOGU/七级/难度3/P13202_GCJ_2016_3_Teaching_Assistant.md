# [GCJ 2016 #3] Teaching Assistant

## 题目描述

You are taking a programming course which is graded using problem sets of different types. The course goes for a positive even number of days. You start the course with no problem sets. On each day of the course, you must do exactly one of the following:

* Request a "Coding" problem set.
* Request a "Jamming" problem set.
* Submit a problem set for grading. You must have at least one problem set to choose this option. If you have multiple problem sets, you must submit the one among those that was requested **most recently**, regardless of its type.

All problem sets are different. There is no requirement on how many sets of each type must be submitted. Once you submit a set, you no longer have that set. Any problem sets that you have not submitted before the end of the course get you no points.

The problem sets are requested from and submitted to an artificially-intelligent teaching assistant. Strangely, the assistant has different moods — on each day it is in the mood for either "Coding" or "Jamming".

* When you request a problem set:
    * If the requested topic matches the assistant's mood, it assigns a problem set worth a maximum of 10 points.
    * If the requested topic does not match its mood, it assigns a problem set worth a maximum of 5 points.
* When you submit a problem set:
    * If the topic of the submitted set matches the assistant's mood that day, it gives you the maximum number of points for that set.
    * If the topic of the submitted set does not match its mood that day, it gives you 5 points fewer than the maximum number of points for that set.

For example:

* If you request a "Coding" problem set on a day in which the assistant is in a "Coding" mood, and submit it on a day in which it is in a "Jamming" mood, you will earn 5 points: the problem set is worth a maximum of 10, but the assistant gives 5 points fewer than that.
* If you request a "Jamming" problem set on a day in which the assistant is in a "Coding" mood, and submit it on a day in which it is in a "Jamming" mood, you will earn 5 points: the set is worth a maximum of 5, and the assistant gives you the maximum number of points.

Thanks to some help from a senior colleague who understands the assistant very well, you know what sort of mood the assistant will be in on each day of the course. What is the maximum total score that you will be able to obtain?

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$; $\mathbf{T}$ test cases follow. Each test case consists of one line with a string $\mathbf{S}$ of $\mathbf{C}$ and/or $\mathbf{J}$ characters. The i-th character of $\mathbf{S}$ denotes the assistant's mood on the i-th day of the course. If it is $\mathbf{C}$, it is in the mood for "Coding"; if it is $\mathbf{J}$, it is in the mood for "Jamming".

## 输出格式

For each test case, output one line containing `Case #x: y`, where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is the maximum number of points you can obtain for that case.

## 样例

### 样例输入 1
```
5
CCJJ
CJCJ
CJJC
CJJJ
CCCCCC
```

### 样例输出 1
```
Case #1: 20
Case #2: 10
Case #3: 20
Case #4: 15
Case #5: 30
```

## 提示

**Sample Explanation**

This strategy is optimal for sample case #1:
- Day 1: Request a "Coding" problem set (call it C1).
- Day 2: Submit C1.
- Day 3: Request a "Jamming" problem set (call it J1).
- Day 4: Submit J1.

The following strategy is optimal for sample cases #2, #3, and #4: request C1, request J1, submit J1, submit C1.

For case #2, for example, note that you could not request C1, request J1, and then submit C1. Only the most recently requested problem set can be submitted.

In sample case #5, you can alternate between requesting a "Coding" problem set on one day, and submitting it on the next day.

**Sample Explanation**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- The length of $\mathbf{S}$ is even.

## 解题思路

### 问题分析

给定助教每天的心情序列（C 或 J），学生每天可以请求一套题目或提交一套题目。请求时：
- 心情匹配得 10 分，不匹配得 5 分
提交时：
- 心情匹配得满分（10 或 5），不匹配扣 5 分

由于提交时心情匹配与否的规则对称，可以证明：每对（请求，提交）的最优得分只取决于两天的心情是否相同——相同得 10 分，不同得 5 分。

### 核心思路

总天数 $n$，共 $L = n/2$ 对。每对基础得分为 5 分，若心情相同额外得 5 分。因此：

$$\text{总分} = 5L + 5 \times (\text{相同心情的配对数})$$

问题转化为：在不交叉配对的约束下，最大化相邻相同心情的配对数。

### 算法流程

这等价于**自由群归约**问题——栈模拟：

1. 初始化空栈
2. 遍历字符串每个字符：
   - 若栈非空且栈顶与当前字符相同，则弹出栈顶，配对数 +1
   - 否则将当前字符压入栈
3. 最终答案为 $5L + 5 \times \text{配对数}$

### 复杂度分析

- **时间复杂度**：$O(n)$，单次遍历
- **空间复杂度**：$O(n)$，栈空间

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    int T; cin >> T;
    for(int t=1; t<=T; ++t){
        string s; cin >> s;
        int n = (int)s.size();
        // Each pair's best value is 10 if the two days share a mood, else 5.
        // Total = 5*L + 5*(#same-mood pairs). Maximize same-mood non-crossing pairs.
        // Equivalent to free-group reduction: cancel adjacent equal letters;
        // #cancellations is invariant and equals the maximum.
        vector<char> st;
        long long same = 0;
        for(char c : s){
            if(!st.empty() && st.back()==c){
                st.pop_back();
                ++same;
            } else {
                st.push_back(c);
            }
        }
        long long L = n/2;
        long long ans = 5*L + 5*same;
        cout << "Case #" << t << ": " << ans << "\n";
    }
    return 0;
}
```
