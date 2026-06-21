#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 50001;
int mu[MAXN], primes[MAXN], pcnt = 0;
bool is_comp[MAXN];

void init() {
    mu[1] = 1;
    for (int i = 2; i < MAXN; ++i) {
        if (!is_comp[i]) { primes[pcnt++] = i; mu[i] = -1; }
        for (int j = 0; j < pcnt && i * primes[j] < MAXN; ++j) {
            is_comp[i * primes[j]] = true;
            if (i % primes[j] == 0) { mu[i * primes[j]] = 0; break; }
            mu[i * primes[j]] = -mu[i];
        }
    }
}

long long solve(int a, int b) {
    long long res = 0;
    int m = min(a, b);
    for (int l = 1, r; l <= m; l = r + 1) {
        r = min(a / (a / l), b / (b / l));
        res += (long long)(a / l) * (b / l) * (mu[r] - mu[l - 1]);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    for (int i = 1; i < MAXN; ++i) mu[i] += mu[i - 1];
    int T;
    cin >> T;
    while (T--) {
        int a, b, d;
        cin >> a >> b >> d;
        a /= d; b /= d;
        cout << solve(a, b) << '\n';
    }
    return 0;
}
