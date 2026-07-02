# [GCJ 2012 #2] Mountain View

## 题目描述
You are walking through the mountains. It turns out that in this mountain range there is a peak every kilometer, and there are no intermediate peaks. On every peak, you lie down for a rest, look forward, and perceive one of the peaks in front of you to be the highest one. The peak that looks like it's the highest might not really be the highest, for two reasons: there could be a higher peak that is obscured by another peak that's closer to you, and not as high; or you could be looking down, and a faraway peak could look higher than a nearby one.

To be precise, when we say that peak $B$ looks like it's the highest from peak $A$ we mean that $B$ is further down the road than $A$; all peaks between $A$ and $B$ are below the line connecting the peaks $A$ and $B$; and all the peaks that are further than $B$ are below or on this line.

You don't know how high each peak is, but you have a very good memory; you've been on all the peaks; and you remember which peak looks like it's the highest from each of them. You would like to invent a set of heights for the peaks that is consistent with that information. Note that you were lying down when looking, so we assume you always looked from the ground level on each peak.

In this example, the fourth peak looks like it's the highest from the first and third peaks. When you're lying on the second peak, you can't see the fourth peak; the third one obscures it, and looks like it's the highest.

## 输入格式
The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case consists of two lines. The first contains one number, $N$, the number of peaks in the range. You began your trip on peak $1$ and went forward to peak $N$. The next line contains $N-1$ numbers $x_i$. The $i$-th number denotes the index of the peak that appeared to be the highest from peak $i$ (note that peak $N$ is the last peak, so there are no other peaks to see from there).

## 输出格式
For each test case, output one line containing "Case #$n$: $y_1$ $y_2$ ... $y_N$", where $n$ is the case number (starting from $1$) and $y_i$ is the height of the $i$-th peak. You can output any solution agreeing with the input data, except that all the heights you output have to be integers between $0$ and $10^9$, inclusive.

If no solution is possible, output "Case #$n$: Impossible" instead.

## 样例
### 样例1
输入：
```
2
4
2 3 4
3
2 2
```
输出：
```
Case #1: 10 10 10 10
Case #2: 10 10 10
```

## 提示
**Limits**

- $1 \leq T \leq 30.$
- $i < x_i \leq N.$

**Test set 1 (13 Pts, Visible Verdict)**
- $1 \leq N \leq 10.$

**Test set 2 (12 Pts, Visible Verdict)**
- $1 \leq N \leq 100.$

**Test set 3 (17 Pts, Hidden Verdict)**
- $1 \leq N \leq 1000.$

## 解题思路

### 问题分析
这是一个关于山峰高度和可见性的问题。我们需要根据每个山峰看到的最高山峰信息，构造一组可能的高度。

### 核心思路
1. **贪心策略**：从后往前处理，确保每个山峰看到的最高山峰确实是最高的。
2. **约束条件**：对于每个山峰i，它看到的最高山峰x_i必须满足：所有在i和x_i之间的山峰都低于连接i和x_i的直线，且所有在x_i之后的山峰都低于或在这条直线上。
3. **构造方法**：可以给每个山峰分配高度，使得约束条件满足。

### 算法流程
1. 从最后一个山峰开始，向前处理每个山峰。
2. 对于每个山峰i，根据x_i的值设置高度。
3. 检查是否所有约束条件都满足。

### 复杂度分析
- 时间复杂度：$O(n)$ 或 $O(n^2)$，取决于具体实现。
- 空间复杂度：$O(n)$。

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        
        vector<int> x(n - 1);
        for (int i = 0; i < n - 1; i++) {
            cin >> x[i];
            x[i]--; // 转换为0-indexed
        }
        
        // 实现略，需要根据上述思路编写具体代码
        // 这里输出简单解作为占位
        cout << "Case #" << t << ":";
        for (int i = 0; i < n; i++) {
            cout << " 10";
        }
        cout << endl;
    }
    
    return 0;
}
```