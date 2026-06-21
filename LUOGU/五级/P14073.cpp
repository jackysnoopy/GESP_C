#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<bool> is_prime(n + 1, true);
    int cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            cnt++;
            if ((long long)i * i <= n) {
                for (int j = i * i; j <= n; j += i)
                    is_prime[j] = false;
            }
        }
    }
    cout << cnt + 1 << "\n";
    return 0;
}
