#include <bits/stdc++.h>
using namespace std;

int cnt[105];

bool check(int pos) {
    if (pos > 100) {
        for (int i = 1; i <= 100; i++) {
            if (cnt[i] > 0) return false;
        }
        return true;
    }
    
    if (cnt[pos] == 0) return check(pos + 1);
    
    // 尝试作为对子
    if (cnt[pos] >= 2) {
        cnt[pos] -= 2;
        if (check(pos)) {
            cnt[pos] += 2;
            return true;
        }
        cnt[pos] += 2;
    }
    
    // 尝试作为刻子
    if (cnt[pos] >= 3) {
        cnt[pos] -= 3;
        if (check(pos)) {
            cnt[pos] += 3;
            return true;
        }
        cnt[pos] += 3;
    }
    
    // 尝试作为顺子
    if (pos <= 98 && cnt[pos] >= 1 && cnt[pos + 1] >= 1 && cnt[pos + 2] >= 1) {
        cnt[pos]--;
        cnt[pos + 1]--;
        cnt[pos + 2]--;
        if (check(pos)) {
            cnt[pos]++;
            cnt[pos + 1]++;
            cnt[pos + 2]++;
            return true;
        }
        cnt[pos]++;
        cnt[pos + 1]++;
        cnt[pos + 2]++;
    }
    
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        for (int i = 1; i <= 100; i++) {
            scanf("%d", &cnt[i]);
        }
        
        bool ok = false;
        for (int i = 1; i <= 100; i++) {
            if (cnt[i] >= 2) {
                cnt[i] -= 2;
                if (check(1)) {
                    ok = true;
                }
                cnt[i] += 2;
                if (ok) break;
            }
        }
        
        printf("%s\n", ok ? "Yes" : "No");
    }
    
    return 0;
}
