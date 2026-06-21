#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<bool> is_comp(n + 1, false);
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (!is_comp[i]) primes.push_back(i);
        for (int j = 0; j < (int)primes.size() && i * primes[j] <= n; ++j) {
            is_comp[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
    for (int p : primes) {
        long long cnt = 0;
        long long pk = p;
        while (pk <= n) { cnt += n / pk; pk *= p; }
        cout << p << " " << cnt << '\n';
    }
    return 0;
}
