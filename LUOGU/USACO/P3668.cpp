#include <iostream>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    cin >> n;
    long long ans = 0;
    for (long long i = 1; i*i <= n; i++) {
        if (n % i == 0) {
            ans += i;
            if (i != n/i) ans += n/i;
        }
    }
    cout << ans << "\n";
    return 0;
}
