# [ICPC 2025 LAC] Keep Fighting

## 题目描述

Bob is playing a card game where he must defeat a monster. Before the game starts, Bob's power is set to $P$, the monster's health is set to $H$, and Bob receives a deck of $N$ cards in his hands.

Each card in the deck belongs to one of the following types:

- **Multiply**: a card of this type has a number $X$ written on it. Playing it multiplies Bob's current power by $X$.
- **Add**: a card of this type also has a number $Y$ written on it. Playing it increases Bob's current power by $Y$.
- **Attack**: a card of this type allows Bob to attack the monster. Playing it reduces the monster's current health by Bob's current power.

The game is played in turns. In each turn, Bob must play exactly one card from his hand, after which the card is moved to a discard pile. If Bob has no cards left in his hand at the end of a turn, he retrieves all cards from the discard pile and can use them again in any order.

The monster is beaten as soon as its health reaches $0$ or less. Is it possible for Bob to beat the monster? If so, what is the minimum number of turns required?

## 输入格式

The first line contains three integers $N$ ($1 \le N \le 50$), $P$ ($0 \le P \le 10^9$) and $H$ ($1 \le H \le 10^9$), indicating respectively the number of cards in the deck, Bob's initial power and the monster's initial health.

Each of the next $N$ lines describes a card. The content of the line depends on the type of the card, as follows:

- **Multiply**: the line contains the character “*” (asterisk) and an integer $X$ ($1 \le X \le 10^9$), representing the multiply factor provided by the card.
- **Add**: the line contains the character “+” (plus sign) and an integer $Y$ ($1 \le Y \le 10^9$), indicating the increment provided by the card.
- **Attack**: the line contains the character “!” (exclamation mark).

## 输出格式

Output a single line with an integer indicating the minimum number of turns required to beat the monster, or the character “*” (asterisk) if it is impossible to beat the monster.

## 样例

### 样例输入 1
```
3 0 20
* 2
!
+ 5
```

### 样例输出 1
```
4
```

### 样例输入 2
```
1 0 1
!
```

### 样例输出 2
```
*
```

### 样例输入 3
```
1 1 1
+ 1
```

### 样例输出 3
```
*
```

## 提示

### Explanation of sample 1:

To beat the monster in 4 turns, Bob can play as follows:

1. Bob plays the $+5$ card, so his power becomes $5$.
2. Bob plays the $*2$ card, so his power becomes $10$.
3. Bob plays the $!$ card, so the monster's health becomes $10$. Since now Bob has no cards in his hands, all three cards go back to him.
4. Bob plays the $!$ card, so the monster's health becomes $0$, and the monster is beaten.

## 解题思路

### 问题分析
Bob 有一副卡牌，包含乘法、加法和攻击三种类型。每次出牌后弃掉，手牌用完后从弃牌堆回收。每回合出一张牌，求最少回合数使怪物血量降至 ≤0。

### 核心思路
贪心模拟：按固定顺序出牌，每次遍历手牌，遇到乘法/加法就使用提升攻击力，遇到攻击就攻击怪物。手牌用完后自动回收，重复执行直到击败怪物或确认无法击败。

### 算法流程
1. 统计攻击牌数量，若为 0 则输出 "*"
2. 初始化 power = P，health = H，turns = 0
3. 循环直到 health ≤ 0：
   - 遍历所有手牌：
     - 乘法牌：power *= X
     - 加法牌：power += Y
     - 攻击牌：health -= power，turns++
     - 若 health ≤ 0，输出 turns 并结束
4. 若循环结束仍未击败，输出 "*"

### 复杂度分析
- 时间复杂度：O(N × rounds)，其中 rounds 为所需回合数
- 空间复杂度：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long P, H;
    cin >> N >> P >> H;

    vector<char> type(N);
    vector<long long> value(N);

    int attack_count = 0;
    for (int i = 0; i < N; i++) {
        cin >> type[i];
        if (type[i] == '!') {
            value[i] = 0;
            attack_count++;
        } else {
            cin >> value[i];
        }
    }

    if (attack_count == 0) {
        cout << "*\n";
        return 0;
    }

    long long power = P;
    int turns = 0;
    long long health = H;

    while (health > 0) {
        for (int i = 0; i < N; i++) {
            if (type[i] == '*') {
                power *= value[i];
            } else if (type[i] == '+') {
                power += value[i];
            } else {
                health -= power;
                turns++;
                if (health <= 0) {
                    cout << turns << "\n";
                    return 0;
                }
            }
        }
    }

    cout << "*\n";
    return 0;
}
```

## 解题思路

### 问题分析
Bob有N张卡牌，包括乘法卡、加法卡和攻击卡。每回合必须打出一张卡，当手牌用完后所有卡牌回到手牌。目标是击败怪物（生命值归0），求最少回合数。

### 核心思路
按固定顺序依次使用所有卡牌。先使用所有增益卡（乘法和加法），最后使用攻击卡。每次打完一轮后卡牌回到手牌，重复此过程直到击败怪物。

### 算法流程
1. 检查是否有攻击卡，若无则输出"*"
2. 按顺序遍历卡牌：遇到乘法/加法就使用，遇到攻击就扣减怪物生命值
3. 每次攻击后检查怪物是否被击败
4. 若一轮结束仍未击败，继续下一轮

### 复杂度分析
- 时间复杂度：O(N × 回合数)
- 空间复杂度：O(N)
