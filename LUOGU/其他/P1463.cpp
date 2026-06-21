#include <iostream>
#include <algorithm>
using namespace std;

const int primes[] = {2,3,5,7,11,13,17,19,23,29};
long long n;
int ans, ans_val;

void dfs(int idx, long long val, int divs, int last_exp) {
    if (divs > ans || (divs == ans && val < ans_val)) {
        ans = divs; ans_val = val;
    }
    if (idx >= 10 || val > n) return;
    long long p = 1;
    for (int e = 1; e <= last_exp; ++e) {
        p *= primes[idx];
        if (val * p > n) break;
        dfs(idx + 1, val * p, divs * (e + 1), e);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    ans = 0; ans_val = 1;
    dfs(0, 1, 1, 30);
    cout << ans_val << '\n';
    return 0;
}
