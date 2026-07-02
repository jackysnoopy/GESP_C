# [BalkanOI 2018] Parentrises

## 题目描述
两类任务：P=1判断括号串是否RGB可读并输出染色；P=2求长度N的RGB可读良括号串个数。

## 输入格式
第一行P和T，接下来T行（括号串或整数N）。

## 输出格式
P=1输出染色方案或impossible；P=2输出答案mod 1e9+7。

## 样例
输入1：
```
1
3
))(()
()()
(()))
```
输出：
```
GRBRBG
BBRBG
impossible
```

## 提示
P=1: len(S) ≤ 10^6; P=2: N ≤ 300。

## 解题思路

### 问题分析
RGB可读：去掉B后是良括号串，去掉R后也是良括号串。

### 核心思路
P=1贪心：从左到右维护B和R的balance，优先保持两者平衡。P=2用DP：dp[b][r]表示B-balance和R-balance的状态数。

### 算法流程
P=1: 贪心选择每字符颜色，保持两个balance≥0。P=2: DP遍历所有N个位置。

### 复杂度分析
P=1: O(N); P=2: O(N³)

## 参考代码
见 P4788.cpp
