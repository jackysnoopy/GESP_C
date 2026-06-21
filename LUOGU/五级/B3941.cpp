#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long ans = 1;
    for (int i = 0; i < n; i++) {
        long long x; cin >> x;
        ans = lcm(ans, x);
    }
    cout << ans << "\n";
    return 0;
}
