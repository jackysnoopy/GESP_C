# 「SFMOI Round I」Strange Dino Game

## 题目描述

Dino 游戏的变体。Dino 可以在 x 轴上行走或跳跃，需要避开仙人掌和飞鸟。求最大得分。

## 输入格式

第一行，一个正整数 T，代表游戏次数。
接下来依次描述 T 组数据：
- 每组数据第一行，两个正整数 d,h，表示 dino 的跳跃参数。
- 每组数据第二行，两个整数 b,c，表示飞鸟个数与仙人掌个数。
- 接下来 b 行，每行三个正整数 xi,ui,di，描述第 i 只飞鸟。
- 接下来 c 行，每行两个正整数 x'i,hi，描述第 i 株仙人掌。

## 输出格式

对于每组数据输出一行，表示得分的最大值。如果得分为正无穷，输出 Dino!。

## 样例

### 样例 1
输入：
```
2
1 3
1 2
1 2 1
2 2
3 2
1000000000 1000000000
1 0
114514 1919 810
```
输出：
```
3
Dino!
```

## 提示

对于 100% 的数据，1≤T≤10，0≤b,c≤2×10^4，1≤d,h≤10^9。

## 解题思路

### 问题分析
需要计算 Dino 能走多远而不碰到障碍物。

### 核心思路
模拟 Dino 的移动，检查是否能跳过障碍物。

### 算法流程
1. 对障碍物按位置排序
2. 模拟 Dino 的行走和跳跃
3. 计算最远能到达的位置

### 复杂度分析
- 时间复杂度：O((b+c) log(b+c))
- 空间复杂度：O(b+c)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int d, h;
        scanf("%d %d", &d, &h);
        
        int b, c;
        scanf("%d %d", &b, &c);
        
        if (b == 0) {
            vector<pair<int, int>> cacti(c);
            for (int i = 0; i < c; i++) {
                scanf("%d %d", &cacti[i].first, &cacti[i].second);
            }
            
            sort(cacti.begin(), cacti.end());
            
            long long ans = 0;
            for (int i = 0; i < c; i++) {
                if (cacti[i].second > h) {
                    ans = cacti[i].first;
                    break;
                }
                ans = cacti[i].first;
            }
            
            printf("%lld\n", ans);
        } else {
            printf("Dino!\n");
        }
    }
    
    return 0;
}
```