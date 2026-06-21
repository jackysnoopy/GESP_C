#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, B;
    cin >> n >> B;
    vector<int> max_prime(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (max_prime[i] == 0) {
            for (int j = i; j <= n; j += i) {
                max_prime[j] = i;
            }
        }
    }
    int ans = 1;
    for (int i = 2; i <= n; i++) {
        if (max_prime[i] <= B) ans++;
    }
    if (n >= 1) ans++;
    cout << ans << "\n";
    return 0;
}
