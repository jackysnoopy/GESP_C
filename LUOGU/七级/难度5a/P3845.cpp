#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int s;
        scanf("%d", &s);
        
        map<pair<int, int>, int> matches;
        int total = 0;
        
        for (int i = 0; i < s; i++) {
            int x, y;
            scanf("%d-%d", &x, &y);
            if (x > y) swap(x, y);
            matches[{x, y}]++;
            total++;
        }
        
        // 每场比赛有3个比分：x-y, (x+1)-y, x-(y+1)
        // 最终比分是5-3时，中间比分可能是1-0, 3-2, 2-3, 3-4, 5-3
        // 每场比赛至少有2个比分（最终比分和中间某个比分）
        
        int games = 0;
        for (auto& [score, cnt] : matches) {
            // 每场比赛至少贡献2个比分
            games += (cnt + 1) / 2;
        }
        
        printf("%d\n", games);
    }
    
    return 0;
}
