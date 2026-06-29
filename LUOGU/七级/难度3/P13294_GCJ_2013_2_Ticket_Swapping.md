# [GCJ 2013 #2] Ticket Swapping

## 题目描述

The city has built its first subway line, with a grand total of $N$ stations, and introduced a new way of paying for travel. Instead of just paying for one ticket and making an arbitrary journey, the price you pay is now based on entry cards.

When entering the subway, each passenger collects an entry card, which specifies the station the passenger entered at. When leaving the subway, the passenger has to give up the entry card, and is charged depending on the distance (in stations traveled) between the entry station specified on the entry card, and the exit station on which the entry card is surrendered. The payment depends on the distance between these stations as follows:

* if they are the same station, you don't pay;
* if they are adjacent stations, you pay $N$ pounds;
* if the distance is two stations, you pay $2N - 1$: a charge $N$ for the first stop and $N - 1$ for the second;
* the third station costs $N-2$ (so you pay $3N - 3$ for a three-station-long trip), the fourth stop $N-3$, and the $i$th stop $N + 1 - i$;
* thus, if you travel from one end of the subway to the other (a distance of $N-1$ stations), you pay $2$ pounds for the last station traveled, and a grand total of $(N^2 + N - 2) / 2$ in total.

After introducing this system the city noticed their gains are not as big as they expected. They figured out this might be due to people swapping their entry cards — so, for instance, if one person enters at station $A$, travels two stations to $B$ and exits, while another person enters at $B$, travels three stations to $C$ and exits, they would normally pay (in total) $2N - 1 + 3N - 3 = 5N - 4$. But if the two people swapped their entry cards at station $B$, then the first one would travel for free (as he would surrender an entry card specifying the station $B$ while exiting a station $B$, and so register a distance of zero); while the second person will exit at station $C$ and surrender an entry card specifying station $A$, which is $5$ stations away, and pays $5N - 10$, at a net loss of six pounds to the city!

The city now wants to learn how much they can possibly lose if this practice becomes widespread. We will consider only one direction (from station $1$ to station $N$, passing through all the stations in order) of the subway, and only one train on this line. We assume a passenger travelling from $o$ to $e$ obtains an entry card at $o$, can swap her entry card any number of times with any other passengers anywhere between $o$ and $e$, including swapping with people who leave at $o$ or those who enter at $e$, and then exit the train at $e$ with some entry card (it is necessary to surrender some entry card to exit the subway). We also assume the passenger will not exit the train in the meantime (that is, will not surrender the currently held card and obtain a new one).

You are given a map of traffic (specifying how many passengers travel this train from which station to which), and you should calculate the city's financial loss, assuming passengers swap their cards to maximize this loss.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case contains the number $N$ of stops (the stops are numbered $1$ to $N$), and the number $M$ of origin-endpoint pairs given. The next $M$ lines contain three numbers each: the origin stop $o_i$, the end stop $e_i$ and $p_i$: the number of passengers that make this journey.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from $1$) and $y$ is the total loss the city can observe due to ticket swapping, modulo $1000002013$.

## 样例

### 样例输入 1
```
3
6 2
1 3 1
3 6 1
6 2
1 3 2
4 6 1
10 2
1 7 2
6 9 1
```

### 样例输出 1
```
Case #1: 6
Case #2: 0
Case #3: 10
```

## 提示

**Sample Explanation**

The first test case is the case described in the problem statement - two passengers meet at station 3 and swap tickets. In the second test case the two passengers don't meet at all, so they can't swap tickets (and so the city incurs no loss). In the third case, only one of the early passengers can swap tickets with the later passenger.

**Limits**

- $1 \leq T \leq 20$.
- $1 \leq o_i < e_i \leq N$

**Small dataset (8 Pts, Test set 1 - Visible)**

- $2 \leq N \leq 100$.
- $1 \leq M \leq 100$.
- $1 \leq p_i \leq 100$.

**Large dataset (11 Pts, Test set 2 - Hidden)**

- $2 \leq N \leq 10^9$.
- $1 \leq M \leq 1000$.
- $1 \leq p_i \leq 10^9$.

## 解题思路

### 问题分析
待补充

### 核心思路
待补充

### 算法流程
待补充

### 复杂度分析
待补充

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <algorithm>
using namespace std;

const long long MOD = 1000002013;
const long long INV2 = (MOD + 1) / 2;   // 2 * INV2 == 1 (mod MOD), MOD is odd

// fare for travelling d stops on a line of N stations:
//   d*N - d*(d-1)/2   (taken mod MOD)
long long cost(long long d, long long N){
    long long a = (d % MOD) * (N % MOD) % MOD;
    long long b = (d % MOD) * ((d - 1) % MOD) % MOD;
    b = b * INV2 % MOD;
    long long res = (a - b) % MOD;
    if(res < 0) res += MOD;
    return res;
}

int main(){
    int T; cin >> T;
    for(int tc=1; tc<=T; ++tc){
        long long N; int M;
        cin >> N >> M;
        // events grouped by station: origins added, destinations removed
        map<long long, pair<long long,long long>> ev;
        long long normal = 0;
        for(int i=0; i<M; ++i){
            long long o, e, p;
            cin >> o >> e >> p;
            normal = (normal + cost(e - o, N) * (p % MOD)) % MOD;
            ev[o].first  += p;   // entry cards picked up at o
            ev[e].second += p;   // entry cards surrendered at e
        }
        // pool of currently held entry cards: origin station -> count
        map<long long,long long> pool;
        long long actual = 0;
        for(auto &pr : ev){
            long long s = pr.first;
            long long addOrig = pr.second.first;
            long long remDest = pr.second.second;
            if(addOrig > 0) pool[s] += addOrig;     // entries happen first
            long long need = remDest;
            while(need > 0){
                auto it = pool.rbegin();            // surrender closest (largest) origin
                long long o = it->first;
                long long cnt = it->second;
                long long take = min(need, cnt);
                actual = (actual + cost(s - o, N) * (take % MOD)) % MOD;
                need -= take;
                cnt -= take;
                if(cnt == 0) pool.erase(o);
                else pool[o] = cnt;
            }
        }
        long long loss = (normal - actual) % MOD;
        if(loss < 0) loss += MOD;
        cout << "Case #" << tc << ": " << loss << "\n";
    }
    return 0;
}
```