#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100;
vector<int> primes;
bool isPrime[MAXN + 1];

void sieve() {
    fill(isPrime, isPrime + MAXN + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= MAXN; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

int main() {
    sieve();
    int n;
    bool first = true;
    while (cin >> n && n) {
        if (!first) cout << "\n";
        first = false;
        
        vector<int> cnt(primes.size(), 0);
        for (int i = 2; i <= n; i++) {
            int tmp = i;
            for (int j = 0; j < (int)primes.size() && primes[j] <= tmp; j++) {
                while (tmp % primes[j] == 0) {
                    cnt[j]++;
                    tmp /= primes[j];
                }
            }
        }
        
        printf("%3d! =", n);
        int line = 0;
        for (int i = 0; i < (int)primes.size() && primes[i] <= n; i++) {
            if (line == 15) {
                printf("\n      ");
                line = 0;
            }
            printf("%3d", cnt[i]);
            line++;
        }
        printf("\n");
    }
    return 0;
}
