#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    if (!(cin >> k)) return 0;
    vector<int> primes;
    for (int x = 2; (int)primes.size() < k; ++x) {
        bool ok = true;
        int sq = (int)sqrt((double)x);
        for (int p : primes) {
            if (p > sq) break;
            if (x % p == 0) { ok = false; break; }
        }
        if (ok) primes.push_back(x);
    }
    for (int i = 0; i < k; ++i) {
        if (i) cout << ' ';
        cout << primes[i];
    }
    cout << '\n';
    return 0;
}
