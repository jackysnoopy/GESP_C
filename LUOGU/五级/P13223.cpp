#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        ll C;
        int D;
        ll V;
        scanf("%lld %d %lld", &C, &D, &V);
        vector<ll> existing(D);
        for (int i = 0; i < D; i++) scanf("%lld", &existing[i]);
        sort(existing.begin(), existing.end());
        
        ll maxReachable = 0;
        int ans = 0;
        int idx = 0;
        
        while (maxReachable < V) {
            if (idx < D && existing[idx] <= maxReachable + 1) {
                maxReachable += C * existing[idx];
                idx++;
            } else {
                ll newDenom = maxReachable + 1;
                maxReachable += C * newDenom;
                ans++;
            }
        }
        
        printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}
