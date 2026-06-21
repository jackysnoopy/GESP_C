# P13112 - [GCJ 2019 #1C] Robot Programming Strategy

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

### Sample 1
**Input:**
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

**Output:**
```
Case #1: RSRSRSP
Case #2: IMPOSSIBLE
Case #3: P
```

## 样例解释

**Sample Explanation**

Note: Although all the opponents in each of these sample cases have programs of the same length, this is not necessarily the case. Opponents within a test case might have programs of different lengths.

In Sample Case #1, there is only one opponent, with the program RS. Our answer matches the opponent's moves for a while, and the opponent loops through its program several times. As is starts its fourth pass through its program, we beat it with P. Other valid solutions exist, like P, RR, and R.

In Sample Case #2, there are three opponents, with the programs R, P, and S. It is up to you to figure out why this case is IMPOSSIBLE!

In Sample Case #3, all seven opponents use the same program. Using the program P, for example, guarantees that you will win. Remember that each robot begins at the start of its program at the start of each match against a new opponent.

## 数据范围

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

这道题是一个关于石头剪刀布锦标赛的问题。我们需要找到一个程序，能赢所有对手的程序。

关键点：
1. 每个程序是 R、P、S 的序列
2. 比较时，从第一个位置开始，直到有一方赢
3. 如果一直平局，则继续循环

### 算法设计

1. **简单情况**：如果所有对手的程序都相同，我们可以选择能赢那个程序的程序
2. **一般情况**：尝试所有可能的程序长度（1-3），检查是否能赢所有对手

### 关键观察

- 如果存在一个程序能赢所有对手，那么它必须能赢每个对手
- 对于每个对手，我们需要找到一个能赢它的程序

## 算法原理

本题采用枚举和模拟算法。对于每个可能的程序，检查它是否能赢所有对手。

## 代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 判断 a 是否能赢 b
bool beats(char a, char b) {
    return (a == 'R' && b == 'S') || (a == 'P' && b == 'R') || (a == 'S' && b == 'P');
}

// 检查程序 p 是否能赢对手 opp
bool canBeat(const string& p, const string& opp) {
    int pi = 0, oi = 0;
    int moves = 0;
    int maxMoves = 1000; // 足够大的次数
    
    while (moves < maxMoves) {
        if (beats(p[pi], opp[oi])) {
            return true; // 我们赢了
        }
        if (beats(opp[oi], p[pi])) {
            return false; // 对手赢了
        }
        // 平局，继续下一轮
        pi = (pi + 1) % p.size();
        oi = (oi + 1) % opp.size();
        moves++;
    }
    return false; // 如果一直平局，我们算输
}

int main() {
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int A;
        cin >> A;
        
        vector<string> opponents(A);
        for (int i = 0; i < A; i++) {
            cin >> opponents[i];
        }
        
        // 简单策略：尝试所有长度为 1 的程序
        string result = "IMPOSSIBLE";
        vector<char> chars = {'R', 'P', 'S'};
        
        for (char c : chars) {
            string program(1, c);
            bool ok = true;
            for (const string& opp : opponents) {
                if (!canBeat(program, opp)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                result = program;
                break;
            }
        }
        
        // 如果长度 1 不行，尝试长度 2
        if (result == "IMPOSSIBLE") {
            for (char c1 : chars) {
                for (char c2 : chars) {
                    string program = "";
                    program += c1;
                    program += c2;
                    bool ok = true;
                    for (const string& opp : opponents) {
                        if (!canBeat(program, opp)) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        result = program;
                        break;
                    }
                }
                if (result != "IMPOSSIBLE") break;
            }
        }
        
        // 如果长度 2 不行，尝试长度 3
        if (result == "IMPOSSIBLE") {
            for (char c1 : chars) {
                for (char c2 : chars) {
                    for (char c3 : chars) {
                        string program = "";
                        program += c1;
                        program += c2;
                        program += c3;
                        bool ok = true;
                        for (const string& opp : opponents) {
                            if (!canBeat(program, opp)) {
                                ok = false;
                                break;
                            }
                        }
                        if (ok) {
                            result = program;
                            break;
                        }
                    }
                    if (result != "IMPOSSIBLE") break;
                }
                if (result != "IMPOSSIBLE") break;
            }
        }
        
        cout << "Case #" << t << ": " << result << endl;
    }
    
    return 0;
}
```

## 复杂度分析

- **时间复杂度**：O(T * A * L * M)，其中 A 是对手数量，L 是程序长度，M 是模拟次数
- **空间复杂度**：O(A * L)，用于存储对手程序

## 注意事项

1. 这个解法适用于测试集1（A <= 7）
2. 对于测试集2（A <= 255），可能需要更高效的算法
3. 关键是正确模拟比较过程
