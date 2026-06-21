#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

int main() {
    long long L, R;
    while (cin >> L >> R) {
        long long sq = (long long)sqrt((double)R) + 1;
        vector<bool> is_prime(sq + 1, true);
        vector<int> small_primes;
        is_prime[0] = is_prime[1] = false;
        for (long long i = 2; i <= sq; ++i) {
            if (is_prime[i]) {
                small_primes.push_back((int)i);
                for (long long j = i * i; j <= sq; j += i)
                    is_prime[j] = false;
            }
        }
        long long sz = R - L + 1;
        vector<bool> seg(sz, true);
        if (L == 1) seg[0] = false;
        for (int p : small_primes) {
            long long start = max((long long)p * p, ((L + p - 1) / p) * p);
            for (long long j = start; j <= R; j += p)
                seg[j - L] = false;
        }
        vector<long long> primes;
        for (long long i = L; i <= R; ++i)
            if (seg[i - L]) primes.push_back(i);
        if (primes.size() < 2) {
            cout << "There are no adjacent primes." << endl;
            continue;
        }
        int min_d = INT_MAX, max_d = 0;
        int min_i = 0, max_i = 0;
        for (int i = 1; i < (int)primes.size(); ++i) {
            int d = (int)(primes[i] - primes[i - 1]);
            if (d < min_d) { min_d = d; min_i = i - 1; }
            if (d > max_d) { max_d = d; max_i = i - 1; }
        }
        cout << primes[min_i] << "," << primes[min_i + 1]
             << " are closest, "
             << primes[max_i] << "," << primes[max_i + 1]
             << " are most distant." << endl;
    }
    return 0;
}
