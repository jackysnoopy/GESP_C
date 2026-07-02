#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50005;
int n, m, L;
int x[MAXN];
int dir[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> L;
        for (int i = 0; i < n; i++) cin >> x[i] >> dir[i];
        long long ans = 0;
        sort(x, x + n);
        for (int i = 0; i < n; i++) {
            if (dir[i] == 0) {
                int target = x[i] - L;
                int pos = lower_bound(x, x + n, target) - x;
                if (pos >= 0 && pos < n && dir[pos] == 1 && x[pos] <= x[i] && x[pos] >= x[i] - L) {
                    ans += x[i] - x[pos];
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
