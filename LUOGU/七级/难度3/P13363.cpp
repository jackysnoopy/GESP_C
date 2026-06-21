#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        vector<ll> c(N);
        ll xsum = 0, total = 0, mn = 1e18;
        for (int i = 0; i < N; i++) {
            cin >> c[i];
            xsum ^= c[i];
            total += c[i];
            mn = min(mn, c[i]);
        }
        cout << "Case #" << tc << ": ";
        if (xsum != 0) cout << "NO\n";
        else cout << total - mn << "\n";
    }
    return 0;
}
