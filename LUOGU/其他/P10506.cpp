#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int xr = 0;
        for (int i = 0; i < n; ++i) {
            int a; cin >> a;
            int sg = 0;
            for (int p = 2; p * p <= a; ++p)
                while (a % p == 0) { sg++; a /= p; }
            if (a > 1) sg++;
            xr ^= sg;
        }
        cout << (xr ? "freda" : "rainbow") << '\n';
    }
    return 0;
}
