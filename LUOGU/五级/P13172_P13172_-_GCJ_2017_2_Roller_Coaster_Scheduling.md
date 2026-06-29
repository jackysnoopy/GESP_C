# P13172 - [GCJ 2017 #2] Roller Coaster Scheduling

## 题目描述

You created a new roller coaster that is about to open. Its train consists of a single row of $N$ seats numbered $1$ through $N$ from front to back. Of course, seats closer to the front are more valuable. Customers have already purchased opening-day tickets. Each ticket allows a specific customer to take one ride on the coaster in a particular seat. Some customers may have bought more than one ticket, and they expect to go on one ride for each ticket.

You need to decide how many roller coaster rides there will be on opening day. On each ride, one customer can sit in each seat; some seats on a ride might be left empty. You cannot assign a customer to more than one seat in the same ride, nor can you put two customers on the same seat in any given ride.

You wish to minimize the number of rides required to honor all tickets, to reduce operational costs. To reduce the required number of rides, you can promote any number of tickets. Promoting a ticket means taking a customer's ticket and giving that customer a new ticket for a seat closer to the front of the train (that is, a seat with a lower number). You would prefer to promote as few tickets as possible, since too many promotions might cause customers to get greedy and ask for more promotions in the future.

Given the positions and buyers of all the tickets that have been sold, what is the minimum number of rides needed to honor all tickets, using as many promotions as needed and scheduling the rides optimally? And what is the minimum number of ticket promotions necessary to attain that number of rides? Note that promoting a given customer on a given ride from seat $4$ to seat $2$, for example, counts as only one promotion, not two separate ones.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a single line with three integers $N$, the number of seats in the roller coaster, $C$, the number of potential customers, and $M$, the number of tickets sold. The customers are identified with numbers between 1 and $C$. Then, $M$ lines follow, each containing two integers: $P_i$, the position in the roller coaster assigned to the $i$-th ticket, and $B_i$, the identifier of the buyer of that ticket.

## 输出格式

For each test case, output one line containing `Case #x: y z`, where $x$ is the test case number (starting from 1), $y$ is the minimum number of rides you need to honor all tickets if you use the promotions and schedule the rides optimally, and $z$ is the minimum number of promotions you need to make be able to honor all tickets with $y$ rides.

## 样例

### Sample 1
**Input:**
```
5
2 2 2
2 1
2 2
2 2 2
1 1
1 2
2 2 2
1 1
2 1
1000 1000 4
3 2
2 1
3 3
3 1
3 3 5
3 1
2 2
3 3
2 2
3 1
```

**Output:**
```
Case #1: 1 1
Case #2: 2 0
Case #3: 2 0
Case #4: 2 1
Case #5: 2 1
```

## 样例解释

**Sample Explanation**

Note that the last two sample cases would not appear in the Small dataset.

In Case #1, both customers purchased a ticket for position 2. It is impossible to honor both tickets with a single ride, but promoting either ticket to position 1 allows you to accommodate both tickets on the same round.

Case #2 is a similar story, except both tickets are for position 1. Since you cannot promote those tickets or exchange them for inferior tickets, you are forced to run 2 separate rides, one per customer.

Case #3 features the same customer purchasing both positions. Since you are forced to have 2 rides for that customer, there is no reason to give out any promotions.

In Case #4, notice that there may be both customers and positions with no tickets assigned. In this case, there are three tickets sold for position three. If you promote customer 2 to position 2, for instance, you can have one ride with customer 1 sitting in position 2 and customer 3 sitting in position 3, and a second ride with customer 2 in position 2 and customer 1 in position 3. Additional promotions will not allow you to decrease the number of rides, because customer 1 has two tickets and you need to honor those in different rides, regardless of position.

In Case #5, one optimal solution is to promote one of the $3\ 1$ tickets to $1\ 1$.

## 数据范围

- $1 \leq T \leq 100$.
- $2 \leq N \leq 1000$.
- $1 \leq M \leq 1000$.
- $1 \leq P_i \leq N$.
- $1 \leq B_i \leq C$.

**Small dataset (7 Pts, Test Set 1 - Visible)**
- $C = 2$.

**Large dataset (14 Pts, Test Set 2 - Hidden)**
- $2 \leq C \leq 1000$.

## 解题思路

### 问题分析

这道题是一个关于票务调度的问题。我们需要找到最小的 rides 数量，以及在该 rides 数量下的最小 promotions 数量。

关键点：
1. 每个座位 i 在 rides 次中可以容纳 rides 张票
2. 如果 seatCount[i] > rides，需要 promotion 多出的票到前面的座位
3.  promotion 只能将票从后面的座位移到前面的座位

### 算法设计

1. **计算最小 rides**：
   - 对于每个前缀 1..i，总容量是 rides * i
   - 如果前 i 个座位的总票数超过了 rides * i，则不可能
   - 所以，rides >= ceil(sum_{j=1}^{i} seatCount[j] / i) 对于所有 i
   - 最小 rides K = max_{i=1}^{N} ceil(prefixSum[i] / i)

2. **计算最小 promotions**：
   - 对于每个座位 i，如果 seatCount[i] > K，需要 promotion seatCount[i] - K 张票
   - promotions = sum_{i=1}^{N} max(0, seatCount[i] - K)

## 算法原理

本题采用贪心算法。通过分析前缀和与容量的关系，我们确定了最小 rides 的下界。然后，对于该 rides 数量，我们计算需要的 promotions。

## 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, C, M;
        cin >> N >> C >> M;
        
        vector<int> seatCount(N + 1, 0);
        
        for (int i = 0; i < M; i++) {
            int P, B;
            cin >> P >> B;
            seatCount[P]++;
        }
        
        // 计算 prefixSum
        vector<int> prefixSum(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            prefixSum[i] = prefixSum[i-1] + seatCount[i];
        }
        
        // 计算最小 rides K
        int K = 0;
        for (int i = 1; i <= N; i++) {
            // ceil(prefixSum[i] / i)
            int val = (prefixSum[i] + i - 1) / i;
            K = max(K, val);
        }
        
        // 计算 promotions
        int promotions = 0;
        for (int i = 1; i <= N; i++) {
            if (seatCount[i] > K) {
                promotions += seatCount[i] - K;
            }
        }
        
        cout << "Case #" << t << ": " << K << " " << promotions << endl;
    }
    
    return 0;
}
```

## 复杂度分析

- **时间复杂度**：O(T * N)，其中 N 是座位数量
- **空间复杂度**：O(N)，用于存储座位计数和前缀和

## 注意事项

1. 这个解法适用于所有测试集
2. 关键是正确理解 promotion 的定义和最小 rides 的计算方法
3. 使用前缀和来高效计算前缀的最大需求
