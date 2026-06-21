#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long ans = 0, cur = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cur = max(cur + x, (long long)x);
        ans = max(ans, cur);
    }
    cout << ans << "\n";
    return 0;
}
