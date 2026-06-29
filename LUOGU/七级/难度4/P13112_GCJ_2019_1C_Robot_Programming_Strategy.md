# [GCJ 2019 #1C] Robot Programming Strategy

## 题目描述

After many sleepless nights, you have finally finished teaching a robotic arm to make the hand gestures required for the Rock-Paper-Scissors game. Now you just need to program it to compete in the upcoming robot tournament!

In this tournament, each robot uses a program that is a series of moves, each of which must be one of the following: R (for "Rock"), P (for "Paper"), or S (for "Scissors"). Paper beats Rock and loses to Scissors; Rock beats Scissors and loses to Paper; Scissors beats Paper and loses to Rock.

When two robots face off in a match, the first robot to play a winning move wins. To start, each robot plays the first move of its program. If the two moves are different, one of the moves beats the other and thus one of the robots wins the match. If the moves are the same, each robot plays the next move in its program, and so on.

Whenever a robot has reached the end of its program and needs its next move, it returns to the start of its program. So, for example, the fifth move of a robot with the program RSSP would be R. If a match goes on for over a googol ($10^{100}$) of moves, the judges flip a fair coin to determine the winner.

Once a match is over, the winning robot resets, so it has no memory of that match. In its next match, it starts by playing the first move of its program, and so on.

The tournament is played in K rounds and has a single-elimination "bracket" structure. There are N = $2^K$ robots in total, numbered 0 through N - 1. In the first round, robot 0 plays a match against robot 1, robot 2 plays a match against robot 3, and so on, up to robots N - 2 and N - 1. The losers of those matches are eliminated from the tournament. In the second round, the winner of the 0-1 match faces off against the winner of the 2-3 match, and so on. Once we get to the K-th round, there is only one match, and it determines the overall winner of the tournament.

All of the other contestants are so confident that they have already publicly posted their robots' programs online. However, the robots have not yet been assigned numbers, so nobody knows in advance who their opponents will be. Knowing all of the other programs, is it possible for you to write a program that is guaranteed to win the tournament, no matter how the robot numbers are assigned?

## 输入格式

The first line of the input gives the number of test cases, $T$; $T$ test cases follow. Each test case begins with one line containing an integer $A$: the number of adversaries (other robots) in the tournament. Then, there are $A$ more lines; the i-th of these contains a string $C_i$ of uppercase letters that represent the program of the i-th opponent's robot.

## 输出格式

For each test case, output one line containing `Case #x: y`. If there is a string of between 1 and 500 characters that is guaranteed to win the tournament, as described above, then $y$ should be the string of uppercase letters representing that program. Otherwise, $y$ should be IMPOSSIBLE, in uppercase letters.

## 样例

### 样例输入 1
```
3
1
RS
3
R
P
S
7
RS
RS
RS
RS
RS
RS
RS
```

### 样例输出 1
```
Case #1: RSRSRSP
Case #2: IMPOSSIBLE
Case #3: P
```

## 提示

**Sample Explanation**

Note: Although all the opponents in each of these sample cases have programs of the same length, this is not necessarily the case. Opponents within a test case might have programs of different lengths.

In Sample Case #1, there is only one opponent, with the program RS. Our answer matches the opponent's moves for a while, and the opponent loops through its program several times. As is starts its fourth pass through its program, we beat it with P. Other valid solutions exist, like P, RR, and R.

In Sample Case #2, there are three opponents, with the programs R, P, and S. It is up to you to figure out why this case is IMPOSSIBLE!

In Sample Case #3, all seven opponents use the same program. Using the program P, for example, guarantees that you will win. Remember that each robot begins at the start of its program at the start of each match against a new opponent.

**Limits**

- $1 \leqslant T \leqslant 100 .$
- Each character in $\mathbf{C}_{\mathbf{i}}$ is uppercase $\mathbf{R}, \mathbf{P}$, or $\mathbf{s}$, for all $\mathbf{i}$.
- $\mathbf{A}=2^{\mathbf{K}}-1$ for some integer $\mathbf{K} \geqslant 1$.

**Test set 1 (10 Pts, Visible)**

- $1 \leqslant \mathbf{A} \leqslant 7$.
- $\mathbf{C}_{\mathbf{i}}$ is between 1 and 5 characters long, for all $\mathbf{i}$.

**Test set 2 (18 Pts, Hidden)**

- $1 \leqslant \mathbf{A} \leqslant 255$.
- $\mathbf{C}_{\mathbf{i}}$ is between 1 and 500 characters long, for all $\mathbf{i}$.

## 解题思路

### 问题分析
在一个机器人编程锦标赛中，需要找到一个能击败所有对手的程序。每个程序由R（石头）、P（布）、S（剪刀）组成。比赛规则：第一个出现胜负的回合决定胜者，如果超过$10^{100}$个回合则抛硬币决定。

### 核心思路
采用贪心策略逐步构建程序。每次添加一个字符，检查当前候选程序是否能在有限回合内击败所有对手。由于程序长度限制为500，可以在O(500)长度内找到解或判定无解。

### 算法流程
1. 读入所有对手的程序
2. 初始化result为空字符串，possible为true
3. 从长度1到500遍历：
   - 对于每个位置，尝试添加'R'、'P'、'S'三个字符
   - 对于每个候选程序，检查是否能击败所有对手：
     - 模拟每场比赛，检查在有限回合内是否出现胜负
     - 如果能击败所有对手，则更新result，标记possible=false并跳出
4. 如果result为空则输出"IMPOSSIBLE"，否则输出result

### 复杂度分析
- 时间复杂度：$O(500 \times 3 \times A \times 500) = O(750000A)$，最坏情况下需要尝试500个位置，每个位置3种选择，对A个对手各模拟500回合
- 空间复杂度：$O(A \times L)$，存储所有对手程序，L为最大程序长度

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int A;
        cin >> A;

        vector<string> programs(A);
        for (int i = 0; i < A; i++) cin >> programs[i];

        string result = "";
        bool possible = true;

        for (int len = 1; len <= 500 && possible; len++) {
            for (char c : {'R', 'P', 'S'}) {
                string candidate = result + c;
                bool beats_all = true;

                for (auto& prog : programs) {
                    bool beats = false;
                    for (int i = 0; i < len; i++) {
                        char my_move = candidate[i % candidate.size()];
                        char their_move = prog[i % prog.size()];

                        if (my_move == 'R' && their_move == 'S') beats = true;
                        else if (my_move == 'P' && their_move == 'R') beats = true;
                        else if (my_move == 'S' && their_move == 'P') beats = true;

                        if (beats) break;
                    }

                    if (!beats) {
                        beats_all = false;
                        break;
                    }
                }

                if (beats_all) {
                    result = candidate;
                    possible = false;
                    break;
                }
            }
        }

        cout << "Case #" << t << ": ";
        if (result.empty()) cout << "IMPOSSIBLE\n";
        else cout << result << "\n";
    }

    return 0;
}
```
