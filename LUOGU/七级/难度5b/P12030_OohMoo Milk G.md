# [USACO25OPEN] OohMoo Milk G

## 题目描述

农夫约翰正在生产他世界闻名的 OohMoo 牛奶以获取利润。他有 $N$ 个（$1 \leq N \leq 10^5$）瓶子需要装牛奶，每个瓶子初始含有 $m_i$（$0 \leq m_i \leq 10^9$）单位的牛奶。每天，他会选择 $A$ 个（$1 \leq A \leq N$）瓶子，每个被选中的瓶子增加 $1$ 单位牛奶。

不幸的是，他的竞争对手农夫 Nhoj 知道这个生产过程并计划破坏。每天在农夫约翰添加牛奶后，农夫 Nhoj 会偷偷从 $B$ 个（$0 \leq B < A$）不同的非空瓶子中各偷走 $1$ 单位牛奶。为了不被发现，农夫 Nhoj 确保 $B$ 严格小于 $A$。

经过 $D$ 天（$1 \leq D \leq 10^9$）后，农夫约翰将出售他的牛奶。如果一个瓶子含有 $M$ 单位牛奶，它将卖出 $M^2$ moonies 的价钱。

设 $P$ 为唯一确定的利润值，使得无论农夫 Nhoj 如何操作，农夫约翰都能保证至少获得 $P$ 利润；同时无论农夫约翰如何操作，农夫 Nhoj 都能确保农夫约翰最多获得 $P$ 利润。请输出 $P$ 对 $10^9+7$ 取模的结果。

## 输入格式

```
N D
A B
m1 m2 ... mN
```

## 输出格式

Output a single integer, the profit $P$ modulo $10^9+7$.

## 样例

### 样例 1
**输入：**
```
5 4
4 2
4 10 8 10 10
```
**输出：**
```
546
```

### 样例 2
**输入：**
```
10 5
5 1
1 2 3 4 5 6 7 8 9 10
```
**输出：**
```
777
```

### 样例 3
**输入：**
```
5 1000000000
3 1
0 1 2 3 4
```
**输出：**
```
10
```

## 数据范围

- $1 \leq N \leq 10^5$
- $1 \leq D \leq 10^9$
- $1 \leq A \leq N$
- $0 \leq B < A$
- $0 \leq m_i \leq 10^9$

## 解题思路

### 关键观察
1. **博弈分析**：
   - 每天：农夫约翰增加A瓶牛奶，农夫Nhoj减少B瓶牛奶
   - 由于B < A，总体牛奶量每天净增加A-B单位
   - 最终利润取决于各瓶子牛奶量的平方和

2. **均衡点P**：
   - 农夫约翰能保证的最小利润 = 农夫Nhoj能确保的最大利润
   - 这是一个零和博弈，存在唯一的均衡点

3. **最优策略**：
   - 农夫约翰会尽量平衡各瓶子的牛奶量，使总利润最大
   - 农夫Nhoj会尽量不平衡，使总利润最小
   - 长期来看，所有瓶子的牛奶量会趋向于平均值

### 数学推导
1. **总牛奶量**：$S = \sum_{i=1}^{N} m_i + (A - B) \times D$
2. **平均值**：$\mu = \lfloor S / N \rfloor$，余数 $r = S \mod N$
3. **最终分布**：$r$ 个瓶子牛奶量为 $\mu + 1$，$N - r$ 个瓶子牛奶量为 $\mu$
4. **利润计算**：$P = r \times (\mu + 1)^2 + (N - r) \times \mu^2$

### 算法设计
1. 计算总牛奶量 $S$
2. 计算平均值 $\mu$ 和余数 $r$
3. 计算利润 $P = r \times (\mu + 1)^2 + (N - r) \times \mu^2$
4. 对 $10^9 + 7$ 取模输出

### 复杂度分析
- 时间复杂度：$O(N)$
- 空间复杂度：$O(N)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

const long long MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long D;
    cin >> N >> D;
    
    int A, B;
    cin >> A >> B;
    
    vector<long long> m(N);
    for (int i = 0; i < N; i++) {
        cin >> m[i];
    }
    
    long long total_milk = 0;
    for (long long mi : m) {
        total_milk += mi;
    }
    total_milk += (A - B) * D;
    
    long long avg = total_milk / N;
    long long remainder = total_milk % N;
    
    long long profit = 0;
    for (int i = 0; i < N; i++) {
        long long final_milk = avg;
        if (i < remainder) {
            final_milk++;
        }
        profit = (profit + final_milk * final_milk) % MOD;
    }
    
    cout << profit << endl;
    
    return 0;
}
```