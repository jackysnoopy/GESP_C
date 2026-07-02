# UVA296 - Pythagorean Triples (毕达哥拉斯三元组)

## 题意
给定n，统计所有满足a² + b² = c²且a ≤ b ≤ c ≤ n的毕达哥拉斯三元组(a, b, c)的个数。

## 解法
暴力枚举a和b，检查c² = a² + b²是否是完全平方数且c ≤ n。

## 复杂度
- 时间：O(n² × sqrt(n))
- 空间：O(1)
