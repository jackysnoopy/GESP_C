# [ICPC 2021 Yokohama R] Lottery Fun Time

## 题目描述

:::align{right}
![](https://cdn.luogu.com.cn/upload/image_hosting/lm75f05j.png)
:::

The biggest fun of lottery is not in receiving the (usually a tiny amount of) prize money, but in dreaming of the big fortune you may possibly (that is, virtually never) receive.

You have a number of lottery tickets at hand, each with a six-digit number. All the numbers are different, of course. Tomorrow is the drawing day and the prizes are the following.

- The first prize of $300,000$ yen is won by the ticket with exact match of all the six digits with the six-digit first prize winning number.
- The second prizes of $4,000$ yen are won by all of the tickets with their last four digits matching the four-digit second prize winning number.
- The third prizes of $500$ yen are won by all of the tickets with their last two digits matching any of the three two-digit third prize winning numbers.

The six digits on the lottery tickets and all of the winning numbers may start with zeros.

The last two digits of all the prize winning numbers are made different so that tickets winning the third prize cannot also win the first nor the second prizes. Note that this rule also made the last two digits of the first and the second prize winning numbers different.

To enjoy the climax of the lottery fun time, you decided to calculate the possible maximum amount you may win with your tickets. You have too many tickets to hand-calculate it, but it should also be your joy to write a program for making the calculation.

## 输入格式

The first line of the input has a positive integer $n$ ($n \leq 10^5$), which is the number of tickets you have at hand. Each of the following $n$ lines has the six-digit number on one of your tickets. All the $n$ numbers are different from one another.

## 输出格式

Output in a line a single integer, which is the maximum possible total of winning prizes with the tickets you have.

## 样例

### 样例输入1
```7
034207
924837
372745
382947
274637
083907
294837
```

### 样例输出1
```309500
```

### 样例输入2
```10
012389
456789
234589
678989
890189
567889
123489
263784
901289
345689
```

### 样例输出2
```304500
```

## 提示

For the first sample, the following combination of prize winners allows the maximum total amount of $309500$ yen.

- The first prize winner of $382947$ makes one ticket with that number win $300000$ yen.
- The second prize winner of $4837$ makes two tickets, $924837$ and $294837$, win $4000$ yen each.
- The third prize winners $07$ and $45$ make three tickets, $034207$, $083907$, and $372745$, win $500$ yen each. $37$ cannot be a third prize winner, as the second prize winner, $4837$, has the final two digits of $37$. The ticket $274637$, thus, wins nothing. You have no more tickets to win whatever the remaining third prize winner may be.

For the second sample, nine out of the ten tickets have the same last two digits, $89$, and thus the third prize winner of $89$ allows nine third prizes, totaling $4500$ yen. This is more than the second prize of $4000$ yen possibly won by one of these nine tickets. The only remaining ticket $263784$ should, of course, win the first prize.

## 解题思路

### 问题分析

彩票问题。

### 核心思路

排序后计算加权和。

### 算法流程

1. 排序
2. 按公式累加

### 复杂度分析

O(n log n)时间，O(n)空间。
