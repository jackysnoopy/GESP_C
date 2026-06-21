# [USACO07NOV] Sunscreen G

## 题目描述
有 $C$ 头奶牛进行日光浴，第 $i$ 头奶牛需要 $minSPF[i]$ 到 $maxSPF[i]$ 单位强度之间的阳光。

每头奶牛在日光浴前必须涂防晒霜，防晒霜有 $L$ 种，涂上第 $i$ 种之后，身体接收到的阳光强度就会稳定为 $SPF[i]$，第 $i$ 种防晒霜有 $cover[i]$ 瓶。

求最多可以满足多少头奶牛进行日光浴。

## 输入格式
第一行输入整数 $C$ 和 $L$。

接下来的 $C$ 行，按次序每行输入一头牛的 $minSPF$ 和 $maxSPF$ 值，即第 $i$ 行输入 $minSPF[i]$ 和 $maxSPF[i]$。

再接下来的 $L$ 行，按次序每行输入一种防晒霜的 $SPF$ 和 $cover$ 值，即第 $i$ 行输入 $SPF[i]$ 和 $cover[i]$。

每行的数据之间用空格隔开。

## 输出格式
输出一个整数，代表最多可以满足奶牛日光浴的奶牛数目。

## 样例
### 样例 1
```
3 2
3 10
2 5
1 5
6 2
4 1
```
```
2
```

## 提示
样例解释：给第一头奶牛涂第一种防晒霜，第二头奶牛涂第二种防晒霜。


---


对于 $100\%$ 的数据，$1\le C,L\le 2500$，$1\le minSPF[i]\le maxSPF[i]\le 1000$，$1\le SPF[i]\le 1000$，$1\le cover[i]\le 2500$。

## 解题思路

### 问题分析
C 头奶牛各有所需的 SPF 区间 [min, max]。有 L 种防晒霜，每种有 SPF 值和数量。每头奶牛最多涂一种防晒霜，求最多满足多少头。

### 核心思路
贪心：将奶牛按 min 降序排列，防晒霜按 SPF 值排序。对每头奶牛选择可用的 SPF 最小的防晒霜。

### 算法流程
1. 读入 C, L
2. 奶牛按 minSPF 降序排序
3. 防晒霜按 SPF 从小到大排序
4. 对每头奶牛，找 SPF 在 [min,max] 内的防晒霜
5. 使用后减少数量

### 复杂度分析
- 时间复杂度：O(C log C + L log L)
- 空间复杂度：O(C + L)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Cow {
    int mn, mx;
};

struct Lotion {
    int spf, cnt;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int C, L;
    cin >> C >> L;
    
    vector<Cow> cows(C);
    for (int i = 0; i < C; i++)
        cin >> cows[i].mn >> cows[i].mx;
    
    vector<Lotion> lotions(L);
    for (int i = 0; i < L; i++)
        cin >> lotions[i].spf >> lotions[i].cnt;
    
    sort(cows.begin(), cows.end(), [](const Cow& a, const Cow& b) {
        return a.mn > b.mn;
    });
    sort(lotions.begin(), lotions.end(), [](const Lotion& a, const Lotion& b) {
        return a.spf < b.spf;
    });
    
    int ans = 0;
    for (const auto& cow : cows) {
        for (auto& lotion : lotions) {
            if (lotion.cnt > 0 && lotion.spf >= cow.mn && lotion.spf <= cow.mx) {
                lotion.cnt--;
                ans++;
                break;
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}
```
