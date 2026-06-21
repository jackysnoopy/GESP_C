# [GCJ 2010 Finals] Candy Store

## 题目描述

Owning a candy store is tough! You have to optimize all kinds of things. Lately you've been selling a very popular kind of candy called Whizboppers. These candies become rotten very quickly, which gives them the following properties:

- You must buy new Whizboppers from your supplier every morning.
- You must sell Whizboppers in the boxes you bought from your supplier that morning.

You can order Whizboppers from your supplier in boxes that contain any integer number of grams.

Every day up to $k$ people visit your store, and, starting from the first person, they will choose an integer number of cents to spend on Whizboppers: between $1$ and $C$ cents inclusive. You're going to sell Whizboppers for $1$ cent per gram; so if a person wants to spend $4$ cents, you will give that person exactly $4$ grams of candy. You might do this by giving the person a $4$-gram box, or perhaps a $2$-gram box and two $1$-gram boxes.

What is the minimum number of boxes you need to order so that, no matter what amount each person orders, you can always give all of the people the mass of Whizboppers they want?

Note: When a person chooses how much candy to buy, you know what other people have already bought, but you don't know what future people will buy.

For example, if up to $2$ people visit your store every day, and they spend up to $2$ cents each ($k=2$, $C=2$), you could buy four $1$-gram boxes from your supplier. But you can do better: if you buy two $1$-gram boxes and one $2$-gram box, you can satisfy your customers. Here's how:

```
First Person   Boxes given   Second Person   Boxes given
--------------------------------------------------------
  2 cents      1 x 2-gram      2 cents       2 x 1-gram
                               1 cent        1 x 1-gram
  -----------------------------------------------------
  1 cent       1 x 1-gram      2 cents       1 x 2-gram
                               1 cent        1 x 1-gram
```

Regardless of what the first person orders, you can give out boxes so that the second person can still get the right amount of candy. So for $k=2, C=2$, you can serve any sequence of orders with $3$ boxes.

## 样例

--- Sample 1 ---
Input:
4
1 5
2 2
10 3
2 50
Output:
Case #1: 3
Case #2: 3
Case #3: 19
Case #4: 11

## 解题思路

### 问题分析

待补充

### 核心思路

待补充

### 算法流程

待补充

### 复杂度分析

待补充
