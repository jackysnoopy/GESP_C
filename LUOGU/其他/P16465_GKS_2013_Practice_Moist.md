# [GKS 2013 Practice] Moist

## 题目描述

Moist has a hobby -- collecting figure skating trading cards. His card collection has been growing, and it is now too large to keep in one disorganized pile. Moist needs to sort the cards in alphabetical order, so that he can find the cards that he wants on short notice whenever it is necessary.

The problem is -- Moist can't actually pick up the cards because they keep sliding out his hands, and the sweat causes permanent damage. Some of the cards are rather expensive, mind you. To facilitate the sorting, Moist has convinced Dr. Horrible to build him a sorting robot. However, in his rather horrible style, Dr. Horrible has decided to make the sorting robot charge Moist a fee of $1$ whenever it has to move a trading card during the sorting process.

Moist has figured out that the robot's sorting mechanism is very primitive. It scans the deck of cards from top to bottom. Whenever it finds a card that is lexicographically smaller than the previous card, it moves that card to its correct place in the stack above. This operation costs $1$, and the robot resumes scanning down towards the bottom of the deck, moving cards one by one until the entire deck is sorted in lexicographical order from top to bottom.

As wet luck would have it, Moist is almost broke, but keeping his trading cards in order is the only remaining joy in his miserable life. He needs to know how much it would cost him to use the robot to sort his deck of cards.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each one starts with a line containing a single integer, $N$. The next $N$ lines each contain the name of a figure skater, in order from the top of the deck to the bottom.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from $1$) and $y$ is the number of dollars it would cost Moist to use the robot to sort his deck of trading cards.

## 样例

### 样例输入1
```2
2
Oksana Baiul
Michelle Kwan
3
Elvis Stojko
Evgeni Plushenko
Kristi Yamaguchi
```

### 样例输出1
```Case #1: 1
Case #2: 0
```

## 提示

### Limits

$1 \le T \le 100$.

Each name will consist of only letters and the space character. Each name will contain at most $100$ characters. No name with start or end with a space. No name will appear more than once in the same test case. Lexicographically, the space character comes first, then come the upper case letters, then the lower case letters.

**Small dataset**

$1 \le N \le 10$.

**Large dataset**

$1 \le N \le 100$.

## 解题思路

### 问题分析

机器人从上到下扫描，当发现某张卡片字典序小于前一张时，将其移到正确位置，花费 $1$ 美元。

### 核心思路

统计有多少张卡片的字典序小于前面所有卡片中的最大值。每出现一次这样的逆序，就需要花费 $1$ 美元。

### 算法流程

1. 读入 $T$ 组测试数据
2. 对每组数据，读入 $N$ 张卡片名称
3. 维护当前遇到的最大字典序名称 $current\_max$
4. 遍历每张卡片，若其字典序小于 $current\_max$，则费用加 $1$
5. 否则更新 $current\_max$

### 复杂度分析

时间复杂度：$O(T \times N \times L)$，其中 $L$ 为字符串平均长度
空间复杂度：$O(N \times L)$

字符串比较，效率足够。
