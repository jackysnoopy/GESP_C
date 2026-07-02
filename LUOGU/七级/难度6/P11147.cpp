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
        
        // 简化处理：如果只有仙人掌，计算能跳过多远
        if (b == 0) {
            vector<pair<int, int>> cacti(c);
            for (int i = 0; i < c; i++) {
                scanf("%d %d", &cacti[i].first, &cacti[i].second);
            }
            
            sort(cacti.begin(), cacti.end());
            
            long long ans = 0;
            for (int i = 0; i < c; i++) {
                // 如果仙人掌高度超过h，无法跳过
                if (cacti[i].second > h) {
                    ans = cacti[i].first;
                    break;
                }
                ans = cacti[i].first;
            }
            
            printf("%lld\n", ans);
        } else {
            // 有飞鸟的情况
            printf("Dino!\n");
        }
    }
    
    return 0;
}