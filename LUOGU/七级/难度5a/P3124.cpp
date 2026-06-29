#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
pair<int, int> bales[MAXN];
int n, B;

int main() {
    scanf("%d%d", &n, &B);
    
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &bales[i].first, &bales[i].second);
    }
    
    sort(bales, bales + n, [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });
    
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (bales[i].second == B) {
            pos = i;
            break;
        }
    }
    
    if (pos == -1) {
        printf("-1\n");
        return 0;
    }
    
    int ans = INT_MAX;
    int left = pos, right = pos;
    int power = 0;
    
    while (left >= 0 && right < n) {
        int leftDist = bales[left].second;
        int rightDist = bales[right].second;
        
        if (B - leftDist <= power || rightDist - B <= power) {
            break;
        }
        
        if (leftDist <= B - power) {
            int need = (B - leftDist) - power;
            if (bales[left].first > power) {
                ans = min(ans, need);
            }
        }
        
        if (rightDist >= B + power) {
            int need = (rightDist - B) - power;
            if (bales[right].first > power) {
                ans = min(ans, need);
            }
        }
        
        power++;
        if (left > 0 && bales[left - 1].second >= B - power) left--;
        if (right < n - 1 && bales[right + 1].second <= B + power) right++;
    }
    
    printf("%d\n", ans == INT_MAX ? -1 : ans);
    
    return 0;
}
