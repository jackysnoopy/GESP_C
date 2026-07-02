# [BalticOI 2011] Meetings (Day2)

## 题目描述
The Society for Saving the World has called their N members to an emergency congress to finally agree on a plan for saving the world. To reach a common decision in any meeting at the congress, the meeting participants proceed as follows:

1. Each of them has a proposal and takes P minutes to present it to the others.
2. After all participants have made their presentations, they vote for the best proposal, which takes V minutes.

For example, if each proposal takes one minute (P = 1) and voting also takes one minute (V = 1), a meeting with 100 participants would reach a decision in 101 minutes. To speed up the overall decision-making process, the participants of the congress have decided to split into groups and work in parallel. Each group selects the best proposal among themselves using the procedure described above. Then the representatives of the groups meet and pick the final plan among the proposals voted best in each group.

For example, if the 100 participants would split into two groups of 40 and 60, respectively, the process could work as follows (again, P = V = 1):
- the larger group takes 61 minutes to select their best proposal;
- the smaller group takes 41 minutes to do the same and then has to wait for the larger group to finish;
- then the two representatives of the groups meet and spend 2 minutes presenting to each other and 1 minute to vote.

The total time spent is thus 61 + 2 + 1 = 64 minutes. But the groups might further divide themselves into subgroups and sometimes it could be useful to split into more than two groups. As a special case, a subgroup of 1 member can decide in no time, as there is no need to present one's own proposal to oneself.

Write a program that, given presentation and voting times P and V, computes the minimal time needed for the N participants of the congress to reach a common decision, assuming they organize their meetings and groups optimally.

## 输入格式
The first and only line of input contains the three integers N, P, and V: N is the number of participants of the congress, P is the presentation time (in minutes), and V is the voting time (in minutes).

## 输出格式
The first and only line of output should contain the integer M, the minimal number of minutes needed for the congress to reach a decision.

## 样例
### 样例1
**输入：**
```
9 1 1
```
**输出：**
```
8
```

### 样例2
**输入：**
```
6 1 2
```
**输出：**
```
8
```

### 样例3
**输入：**
```
6 2 1
```
**输出：**
```
12
```

## 提示
Sample Explanation 1: In sample 1, the nine people should be divided into 3 groups. There should be 3 people in each group.

数据范围:
对于 40% 的数据，1 ≤ N ≤ 5000。
对于 70% 的数据，1 ≤ N ≤ 5 × 10^4。
对于所有数据，1 ≤ N ≤ 10^15, 1 ≤ P,V ≤ 1000。

## 解题思路

### 问题分析
本题要求在给定参与者数量、展示时间和投票时间的情况下，求出最少的决策时间。

### 核心思路
将参与者分成若干组，每组独立决策后再由代表决策。

### 算法流程
1. 枚举可能的分组数
2. 计算每种分组方案的总时间
3. 找出最小时间

### 复杂度分析
- 时间复杂度：O(sqrt(N))
- 空间复杂度：O(1)

## 参考代码
```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, p, v;
    cin >> n >> p >> v;
    
    long long ans = 1e18;
    
    for (long long groups = 1; groups * groups <= n; groups++) {
        long long people = (n + groups - 1) / groups;
        long long time = people * p + groups * v;
        ans = min(ans, time);
        
        people = n / groups;
        if (people > 0) {
            time = people * p + groups * v;
            ans = min(ans, time);
        }
    }
    
    cout << ans << endl;
    return 0;
}
```