#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int MAXK = 55;

int k;
vector<pair<int, int>> sticks; // (length, color)
int color_count[MAXK];

int main() {
    scanf("%d", &k);
    
    for (int i = 1; i <= k; i++) {
        int n;
        scanf("%d", &n);
        color_count[i] = n;
        
        for (int j = 0; j < n; j++) {
            int len;
            scanf("%d", &len);
            sticks.push_back({len, i});
        }
    }
    
    // 按长度排序
    sort(sticks.begin(), sticks.end(), greater<pair<int, int>>());
    
    // 检查相邻的三个不同颜色的棍子是否能组成三角形
    for (int i = 0; i < (int)sticks.size() - 2; i++) {
        int a = sticks[i].first, ca = sticks[i].second;
        int b = sticks[i + 1].first, cb = sticks[i + 1].second;
        int c = sticks[i + 2].first, cc = sticks[i + 2].second;
        
        if (ca != cb && cb != cc && ca != cc) {
            if (a < b + c) {
                printf("%d %d %d %d %d %d\n", ca, a, cb, b, cc, c);
                return 0;
            }
        }
    }
    
    printf("NIE\n");
    return 0;
}
