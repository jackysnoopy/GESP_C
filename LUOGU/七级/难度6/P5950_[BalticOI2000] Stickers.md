# P5950 [BalticOI2000] Stickers

## 题目描述

每盒有 $i_j$ 个数字 $j$ 的不干胶（$j=0\ldots9$），每种不超过9个。从1开始拼数，每次打开新盒，用已有不干胶拼数。拼不出则停止。求能拼多少个数。

## 输入格式

10个整数 $i_0\ldots i_9$。

## 输出格式

能拼的数的个数（答案可能非常大，需高精度输出）。

## 算法思路

### 核心观察

从1开始依次拼数 $1,2,3,\ldots$，每拼一个数就消耗对应数字的不干胶。当某个数字的不干胶用完且下一个数仍需要该数字时停止。

**关键**：设能拼到的最大数为 $N$，则对于每一位数字 $d$（$0\le d\le9$），在 $1\sim N$ 中 $d$ 出现的总次数不能超过 $i_d$。

因此问题转化为：

$$\text{求最大的 } N \text{，使得 } \forall d\in[0,9],\ \text{count\_digit}(d, N) \le i_d$$

### 数位计数公式

$\text{count\_digit}(d, N)$：数字 $d$ 在 $1\sim N$ 中出现的总次数。

对 $N$ 的每一位（从个位开始，设当前位权为 $p=10^k$）：

```
higher = N / (p * 10)    // 高位部分
cur    = (N / p) % 10    // 当前位数字
lower  = N % p            // 低位部分
```

- **$d > 0$**：
  - 完整周期贡献：$\text{higher} \times p$
  - 若 $\text{cur} > d$：额外 $+p$
  - 若 $\text{cur} = d$：额外 $+(\text{lower} + 1)$

- **$d = 0$**（排除前导零）：
  - 若 $\text{higher} = 0$：跳过（最高位不能为0）
  - 否则：$(\text{higher} - 1) \times p$
  - 若 $\text{cur} > 0$：$+p$
  - 若 $\text{cur} = 0$：$+(\text{lower} + 1)$

### 二分答案

由于 $\text{count\_digit}(d, N)$ 关于 $N$ 单调不减，对 $N$ 二分：

1. 找上界：不断倍增直到某个 $N$ 使约束被违反
2. 二分：在 $[\text{lo}, \text{hi}]$ 中找满足所有约束的最大 $N$

### 复杂度

- 每次 $\text{count\_digit}$：$O(\log_{10} N)$
- 二分：$O(\log(\text{answer}))$
- 总计：$O(10 \times \log N \times \log(\text{answer}))$

## 复杂度

- 时间：$O(10 \times \log N \times \log(\text{answer}))$
- 空间：$O(1)$

## 注意事项

- 答案可能超过 `long long` 范围，使用 `__int128` 或高精度
- 输入值也可能很大，需用字符串读入再转换
