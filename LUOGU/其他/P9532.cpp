#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long n, x;
        cin >> n >> x;
        // Array: a[1], a[2]=a[1], a[3]=2*a[1], a[4]=4*a[1], ..., a[n]=2^(n-2)*a[1]
        // a[i] = 2^(i-2)*a[1] for i>=2, a[1] for i=1
        // x appears somewhere. Minimize a[n].
        // If x = a[1] = a[2]: a[n] = 2^(n-2)*x
        // If x = a[k] for k>=2: a[1] = x / 2^(k-2), need x divisible by 2^(k-2)
        //   a[n] = 2^(n-2)*a[1] = 2^(n-2)*x/2^(k-2) = x*2^(n-k)
        // So answer = min over valid k of x*2^(n-k)
        // k=1 or k=2: a[n] = x*2^(n-2)
        // k>=2, x divisible by 2^(k-2): a[n] = x*2^(n-k)
        // Minimize 2^(n-k): maximize k. Max k where 2^(k-2)|x.
        // v2(x) = largest e such that 2^e|x. Then max k-2 = v2(x), k = v2(x)+2.
        // a[n] = x*2^(n-v2(x)-2)
        long long v2 = 0;
        long long tx = x;
        while (tx % 2 == 0) { v2++; tx /= 2; }
        long long maxk = v2 + 2;
        if (maxk > n) maxk = n;
        long long ans = x;
        for (int i = 0; i < n - maxk; i++) ans *= 2;
        // Also consider k=1 or k=2 without divisibility
        long long ans2 = x;
        for (int i = 0; i < n - 2; i++) ans2 *= 2;
        cout << min(ans, ans2) << "\n";
    }
    return 0;
}
