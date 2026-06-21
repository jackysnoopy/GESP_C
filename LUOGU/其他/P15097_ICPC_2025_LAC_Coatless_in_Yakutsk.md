# [ICPC 2025 LAC] Coatless in Yakutsk

## 题目描述

It was your first time visiting Salvador, and you made the rookie mistake of sleeping on the beach. You woke up red, sunburned, and frankly, humiliated. Swearing vengeance against the sun and all its terrible consequences, you decided that your next vacation would be somewhere with a real winter – like Yakutsk, Russia, where the average temperature is $-42^\circ$ Celsius.

But you came prepared! You brought a warm, cozy coat. The coat is perfect, it warms you very well. Maybe too well, as you get sweaty and the coat gets dirty after $C$ days of use. Since your trip lasts more than $C$ days, you must find a way to avoid walking around smelling bad.

To do so, when the coat gets dirty, you cannot wear it until it is washed, but you may also choose to wash it earlier. On any day you do not wear the coat – whether because it is dirty or being washed – you must endure the day’s temperature without its protection. After being washed, the coat is fresh and ready to be worn again. At the start of your trip, the coat is clean.

Given the daily temperatures in Yakutsk for the duration of your trip, you must determine the lowest temperature on a day when you are forced to be without your coat, assuming you schedule wash days optimally to make this temperature as high as possible.

## 输入格式

The first line contains two integers $C$ and $N$ ($1 \le C < N \le 10^5$), indicating respectively the number of days you can wear the coat before it gets dirty, and the duration in days of your holidays.

The second line contains $N$ integers $T_1, T_2, \dots, T_N$ ($-50 \le T_i \le 50$ for $i = 1, 2, \dots, N$), where $T_i$ is the temperature on the $i$-th day.

## 输出格式

Output a single line with an integer indicating the minimum temperature you must endure without your coat.

## 样例

### 样例输入1
```2 6
-20 -10 -5 -10 -2 -40
```

### 样例输出1
```-5
```

## 提示



## 解题思路

### 问题分析

大衣可穿 C 天后需洗，洗时不能穿。N 天行程，每天有温度，求洗衣日中最高可能的最低温度。

### 核心思路

二分答案 mid：能否安排洗衣日使得所有洗衣日温度 >= mid。贪心：每 C+1 天必须洗一天，在 [pos, pos+C] 中找第一个温度 >= mid 的日子作为洗衣日。

### 算法流程

1. 二分温度 [-50, 50]
2. 贪心检查：每 C+1 天必须有一天温度 >= mid
3. 输出最大可行温度

### 复杂度分析

时间 O(N log 100)，空间 O(N)
