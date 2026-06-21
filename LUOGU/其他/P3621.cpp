#include <iostream>
#include <cmath>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    int k;
    cin >> n >> k;
    if (k > 30) { cout << 1 << "\n"; return 0; }
    long long target = 1LL << k;
    long long ans = (n + target - 1) / target;
    cout << ans << "\n";
    return 0;
}
