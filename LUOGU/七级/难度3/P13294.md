# [GCJ 2013 #2] Ticket Swapping

## 题目描述

一条地铁有 $N$ 个车站（编号 $1$ 到 $N$，单向从 1 到 N）。进站时领一张记有进站站的入站卡，出站时交还入站卡并按“进站站与出站站的距离”计费。距离为 $d$ 站时费用为 $\sum_{i=1}^{d}(N+1-i)=dN-\frac{d(d-1)}{2}$（距离 0 免费）。

乘客可在旅途中任意多次与其他乘客交换入站卡（只要两人同时在车上即可），从而让交还的卡对应的进站站不同于自己真正的进站站，以此少付费。给定 $M$ 条出行信息（起点 $o_i$、终点 $e_i$、人数 $p_i$），假设乘客通过换卡使城市收入损失最大化，求城市最大损失（对 $1000002013$ 取模）。

## 输入格式

第一行 $T$。每组第一行 $N,M$；随后 $M$ 行每行 $o_i,e_i,p_i$。

## 输出格式

每组输出 `Case #x: y`，$y$ 为最大损失对 $1000002013$ 取模的值。

## 提示

- $2\le N\le10^9$，$1\le M\le1000$，$1\le o_i<e_i\le N$，$1\le p_i\le10^9$，$1\le T\le20$。
- 样例 1：乘客 $1\to3$ 与 $3\to6$ 在站 3 相遇换卡，前者 0 费用、后者按 $1\to6$（距离 5）付费，损失 6。
- 样例 2：$1\to3$ 与 $4\to6$ 不相遇，无法换卡，损失 0。
- 样例 3：两名 $1\to7$ 与一名 $6\to9$ 中只有一人能完成换卡，损失 10。

## 解题思路

### 问题分析

每名乘客进站领卡（产生一张“起点为 $o_i$”的卡）、出站交卡（消耗一张卡并按“该卡起点到出站站 $e$”的距离计费）。换卡相当于把“卡的起点”与“出站站”重新配对：把全体起点集合 $\{o_i\}$ 与全体出站集合 $\{e_i\}$ 重新匹配，每对 $(o,e)$ 产生费用 $\text{cost}(e-o)$。

可行性约束：一张起点为 $o$ 的卡只能在 $e\ge o$ 的出站站被交还（卡只能随乘客向前走）。由于所有 $o_i<e_i$，可证明任意“满足 $o\le e$ 的双射匹配”都是实时可行的（每个前缀上累计起点数 $\ge$ 累计出站数始终成立）。

不换卡时收入 = $\sum p_i\cdot\text{cost}(e_i-o_i)$（正常配对）。换卡使收入最小化，损失 = 正常收入 $-$ 最小收入。

### 核心思路

费用 $\text{cost}(d)=dN-\frac{d(d-1)}{2}$。注意对任意可行匹配，$\sum d=\sum e-\sum o$ 是定值（与配对无关），故线性部分 $N\sum d$ 固定。最小化总收入 $\iff$ 最大化 $\sum d^2$（因为 $-\frac12\sum d^2$ 项）。

最大化 $\sum d^2$ 即让距离尽量“拉开”：用交换论证可知，对两个起点 $a<b$、两个出站 $e_1<e_2$，交叉配对 $(b\to e_1,\ a\to e_2)$ 比顺配 $(a\to e_1,\ b\to e_2)$ 的 $\sum d^2$ 更大。因此在每个出站站 $e$ 交还卡时，应优先用“当前手持卡中起点最大（离 $e$ 最近）”的那张——这既最小化当前费用，又把小起点留给更远的出站站，使整体 $\sum d^2$ 最大。

### 算法流程

1. 按车站升序处理事件。每个站先加入在此进站的卡（起点 $=$ 该站，数量 $p$），再处理在此出站的卡。
2. 维护手持卡池 `pool`（起点 $\to$ 数量）。对出站站 $e$ 的每张待交卡：取出池中起点最大者 $o$，费用累加 $\text{cost}(e-o)\times\text{数量}$，并从池中扣除。
3. 最小收入 `actual` 即所有交卡费用之和（取模）。
4. 损失 $=(\text{normal}-\text{actual})\bmod MOD$。

模运算要点：$d(d-1)$ 为偶数，除以 2 用乘法逆元 $\text{INV2}=(\text{MOD}+1)/2$（MOD 为奇数）。

### 复杂度分析

事件数 $O(M)$，每次出站最多“整块用完”若干起点（总计不超过不同起点数 $M$）外加一次部分使用，故总操作 $O(M)$，每次 `map` 操作 $O(\log M)$。时间 $O(M\log M)$，空间 $O(M)$。即使 $N\le10^9$ 也只与 $M$ 有关，十分高效。

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
