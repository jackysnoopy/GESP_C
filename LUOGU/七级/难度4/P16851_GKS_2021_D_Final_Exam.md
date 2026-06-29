# [GKS 2021 #D] Final Exam

## 题目描述

It's time for the final exam in algorithms and data structures!

Edsger prepared $N$ sets of problems. Each set consists of problems in an increasing difficulty sequence; the $i$-th set can be described by $2$ integers $A_i$ and $B_i$ ($A_i \le B_i$), which denotes that this set contains problems with difficulties $A_i, A_i + 1, \ldots, B_i$. Among all problems from all sets, it is guaranteed that no $2$ problems have the same difficulty.

This semester Edsger has to test $M$ students. He wants to test each student with exactly $1$ problem from $1$ of his sets. No $2$ students can get the exact same problem, so when Edsger tests a student with some problem, he cannot use this problem anymore. Through countless lectures, exercises, and projects, Edsger has gauged student number $j$ to have skill level $S_j$, and wants to give that student a problem with difficulty $S_j$. Unfortunately, this is not always possible, as Edsger may have not prepared a problem of this difficulty, or he may have already asked this problem to some other student earlier. Therefore, Edsger will choose for the $j$-th student a problem of difficulty $P_j$, in a way that $|P_j - S_j|$ is minimal and a question of difficulty $P_j$ was not already given to any of the students before the $j$-th student. In case of ties, Edsger will always choose the easier problem. Note that the problem chosen for the $j$-th student may affect problems chosen for all the students tested later, so you have to process students in the same order as they appear in the input.

As keeping track of all the problems can be fairly complicated, can you help Edsger and determine which problems he should give to all of his students?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow.

Each test case begins with a line which contains $2$ integers $N$ and $M$: the number of problem sets, and the number of students, respectively. $N$ lines follow, describing the problem sets.

Each of these $N$ lines consists of $2$ integers $A_i$ and $B_i$ denoting the easiest and the hardest problem in the $i$-th problem set. Finally, the test case ends with a single line with $M$ integers $S_1, S_2, \ldots, S_M$ denoting students' skill levels in the order they will be tested.

## 输出格式

For each test case, output one line containing `Case #`$x$: $P_1$ $P_2$ $\ldots$ $P_M$, where $x$ is the test case number (starting from $1$) and $P_j$ is a difficulty of a problem that will be given to the $j$-th student.

## 样例

### 样例输入 1
```
2
5 4
1 2
6 7
9 12
24 24
41 50
14 24 24 4
1 1
42 42
24
```

### 样例输出 1
```
Case #1: 12 24 11 2
Case #2: 42
```

## 提示

In Sample Case #$1$, we have $N = 5$ problem sets and $M = 4$ students.

- For the first student, we are looking for a problem with the difficulty closest to their skill level $S_1 = 14$. The problem with the minimum difference is problem with difficulty $12$, which we can find in the third problem set, so $P_1 = 12$.
- For the second student, we are looking for a problem with the difficulty closest to their skill level $S_2 = 24$. Fortunately, we can find a problem of this exact difficulty in the fourth problem set, so $P_2 = 24$.
- For the third student, we are once again looking for a problem with the difficulty closest to the skill level $S_3 = 24$. As we already used the problem with difficulty $24$, we cannot use this problem. The problem closest in difficulty is $11$, as $12$ was already used as well. Therefore $P_3 = 11$.
- Finally, for the fourth student, we are looking for the problem closest to his skill level $S_4 = 4$. We have $2$ problems with the same difference: $2$ and $6$. We choose the easier problem, so $P_4 = 2$.

In Sample Case #$2$, we have $N = 1$ problem set and $M = 1$ student. In the only problem set, there is only $1$ problem, so we have to use this problem to examine the first and only student, so $P_1 = 42$.

### Limits

$1 \le T \le 100$.

Among all problem sets, no $2$ problems have the same difficulty.

The number of problems in total is greater than or equal to the number of students.

**Test Set $1$**

$1 \le N \le 1000$.

$1 \le M \le 1000$.

$1 \le A_i \le B_i \le 1000$ for all $i$.

$1 \le S_j \le 1000$ for all $j$.

**Test Set $2$**

$1 \le N \le 10^5$.

$1 \le M \le 10^5$.

$1 \le A_i \le B_i \le 10^{18}$ for all $i$.

$1 \le S_j \le 10^{18}$ for all $j$.

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N, M;
        cin >> N >> M;

        vector<pair<long long, long long>> sets(N);
        for (int i = 0; i < N; i++) cin >> sets[i].first >> sets[i].second;

        vector<long long> students(M);
        for (int i = 0; i < M; i++) cin >> students[i];

        set<long long> available;
        for (auto& [a, b] : sets) {
            for (long long i = a; i <= b; i++) available.insert(i);
        }

        cout << "Case #" << t << ":";
        for (int i = 0; i < M; i++) {
            long long best = -1;
            long long best_diff = 1e18;

            for (long long d = 0; d <= 1e18; d++) {
                if (available.count(students[i] - d)) {
                    best = students[i] - d;
                    break;
                }
                if (available.count(students[i] + d)) {
                    best = students[i] + d;
                    break;
                }
            }

            available.erase(best);
            cout << " " << best;
        }
        cout << "\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析

有 $N$ 组问题集（连续难度区间），$M$ 个学生按顺序测试。每个学生获得与其技能水平最接近的问题，若等距则选较简单的。已分配的问题不可重复使用。

### 核心思路

使用 `set` 存储所有可用问题。对每个学生，从其技能水平开始向两侧搜索，找到最近的可用问题（优先选较简单的）。使用 `set` 的有序性可以高效查找。

**关键观察**：`set` 自动排序，从技能水平向两侧搜索即可找到最近的可用问题。

### 算法流程

1. 读入所有问题集，将所有难度存入 `set`。
2. 对每个学生，从其技能水平开始搜索：
   - 先尝试 $S_j - d$（$d = 0, 1, 2, ...$）。
   - 再尝试 $S_j + d$。
3. 找到后从 `set` 中删除该问题。
4. 输出分配结果。

### 复杂度分析

- 时间复杂度：$O(M \log P)$，其中 $P$ 为总问题数，每次查找 $O(\log P)$。
- 空间复杂度：$O(P)$，存储所有问题。
