#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<bool> is_composite(n + 1, false);
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (!is_composite[i]) primes.push_back(i);
        for (int j = 0; j < (int)primes.size() && i * primes[j] <= n; ++j) {
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << primes[k - 1] << '\n';
    }
    return 0;
}
