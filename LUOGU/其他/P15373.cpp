#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int guangStorage = 0;
    long long ans = 0;
    for (int b = 30; b >= 0; b--) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] & (1 << b)) cnt++;
        }
        guangStorage = cnt;
        if (guangStorage > 0) ans += (1LL << b);
    }
    cout << ans << "\n";
    return 0;
}
