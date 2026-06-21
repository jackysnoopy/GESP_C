#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

static const long long MOD = 1000000009LL;

long long safe_mod(long long x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    if (!(cin >> N >> K)) return 0;
    vector<long long> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];
    vector<long long> pos, neg;
    int zeros = 0;
    for (long long x : a) {
        if (x > 0) pos.push_back(x);
        else if (x < 0) neg.push_back(x);
        else zeros++;
    }
    sort(pos.begin(), pos.end());
    sort(neg.begin(), neg.end());
    bool all_zero = pos.empty() && neg.empty();
    if (all_zero) {
        if (K > zeros) cout << 0 << '\n';
        else cout << 0 << '\n';
        return 0;
    }
    bool can_zero = (zeros > 0 || (int)pos.size() + (int)neg.size() >= K);
    long long ans = 1;
    int need = K;
    if (pos.size() + neg.size() < K) {
        cout << 0 << '\n';
        return 0;
    }
    if (neg.size() % 2 == 1 && K < (int)a.size()) {
        int i = 0, j = 0;
        long long best_pos = -1, best_neg = -1;
        if (!pos.empty()) best_pos = pos.back();
        if (!neg.empty()) best_neg = neg[0];
        if (best_pos >= 0 && best_neg < 0) {
            if (best_pos >= -best_neg) {
                for (int t = 0; t < K; ++t) {
                    if (i < (int)pos.size() && (j >= (int)neg.size() || pos[i] <= -neg[j])) {
                        ans = ans * (pos[i] % MOD) % MOD;
                        ++i;
                    } else {
                        ans = ans * (neg[j] % MOD + MOD) % MOD;
                        ++j;
                    }
                }
            } else {
                for (int t = 0; t < K; ++t) {
                    if (i < (int)pos.size() && (j >= (int)neg.size() || pos[i] <= -neg[j])) {
                        ans = ans * (pos[i] % MOD) % MOD;
                        ++i;
                    } else {
                        ans = ans * (neg[j] % MOD + MOD) % MOD;
                        ++j;
                    }
                }
            }
        } else if (best_pos >= 0) {
            for (int t = 0; t < K; ++t) {
                if (i < (int)pos.size() && (j >= (int)neg.size() || pos[i] <= -neg[j])) {
                    ans = ans * (pos[i] % MOD) % MOD;
                    ++i;
                } else {
                    ans = ans * (neg[j] % MOD + MOD) % MOD;
                    ++j;
                }
            }
        } else {
            if (K == (int)a.size()) {
                for (long long x : a) ans = ans * (x % MOD + MOD) % MOD;
            } else {
                for (int t = 0; t < K; ++t) {
                    if (i < (int)pos.size() && (j >= (int)neg.size() || pos[i] <= -neg[j])) {
                        ans = ans * (pos[i] % MOD) % MOD;
                        ++i;
                    } else {
                        ans = ans * (neg[j] % MOD + MOD) % MOD;
                        ++j;
                    }
                }
            }
        }
        cout << safe_mod(ans) << '\n';
        return 0;
    }
    int i = 0, j = 0;
    for (int t = 0; t < K; ++t) {
        if (i < (int)pos.size() && (j >= (int)neg.size() || pos[i] <= -neg[j])) {
            ans = ans * (pos[i] % MOD) % MOD;
            ++i;
        } else {
            ans = ans * (neg[j] % MOD + MOD) % MOD;
            ++j;
        }
    }
    cout << safe_mod(ans) << '\n';
    return 0;
}
