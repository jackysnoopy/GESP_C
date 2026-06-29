#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXB = 50;
ll base[MAXB + 1];

void insert(ll x) {
    for (int i = MAXB; i >= 0; i--) {
        if ((x >> i) & 1) {
            if (base[i]) {
                x ^= base[i];
            } else {
                base[i] = x;
                return;
            }
        }
    }
}

ll query() {
    ll ans = 0;
    for (int i = MAXB; i >= 0; i--) {
        ans = max(ans, ans ^ base[i]);
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        ll x;
        scanf("%lld", &x);
        insert(x);
    }
    
    printf("%lld\n", query());
    
    return 0;
}
