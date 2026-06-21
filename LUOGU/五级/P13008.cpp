#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ll x, y;
        int k;
        cin >> x >> y >> k;
        ll a[35];
        for (int i = 0; i <= k; i++) cin >> a[i];
        for (int i = k + 1; i <= 31; i++) a[i] = INF;

        ll diff = y - x;
        if (diff == 0) { cout << "0\n"; continue; }
        if (diff < 0) diff = -diff;

        // dp[carry+2] for current and next row
        // carry ∈ {-2, -1, 0, 1, 2}
        ll dp[5], ndp[5];
        for (int c = 0; c < 5; c++) dp[c] = INF;
        dp[2] = 0; // carry = 0

        for (int i = 0; i <= 31; i++) {
            int b = (diff >> i) & 1;
            for (int c = 0; c < 5; c++) ndp[c] = INF;

            for (int carry = -2; carry <= 2; carry++) {
                if (dp[carry + 2] == INF) continue;
                ll base = dp[carry + 2];
                int val = b + carry; // val ∈ {-2, -1, 0, 1, 2, 3}

                // 枚举ci（整数），使得(val+ci)是偶数
                // next_carry = (val+ci)/2
                // 代价 += |ci| * a[i]
                for (int ci = -3; ci <= 3; ci++) {
                    int v = val + ci;
                    if (v % 2 != 0) continue;
                    int nc = v / 2;
                    if (nc < -2 || nc > 2) continue;
                    ll cost = base + (ll)abs(ci) * a[i];
                    ndp[nc + 2] = min(ndp[nc + 2], cost);
                }
            }

            for (int c = 0; c < 5; c++) dp[c] = ndp[c];
        }

        ll ans = dp[2]; // carry = 0
        if (ans >= INF) ans = -1;
        cout << ans << "\n";
    }

    return 0;
}
