#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000001;
int memo[MAXN];

int cycle_len(long long n) {
    if (n < MAXN && memo[n] != 0) return memo[n];
    long long orig = n;
    int cnt = 1;
    while (n != 1) {
        if (n & 1) n = 3 * n + 1;
        else n = n / 2;
        cnt++;
        if (n < MAXN && memo[n] != 0) {
            cnt += memo[n] - 1;
            break;
        }
    }
    if (orig < MAXN) memo[orig] = cnt;
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memo[1] = 1;

    int i, j;
    while (cin >> i >> j) {
        int a = min(i, j), b = max(i, j);
        int ans = 0;
        for (int k = a; k <= b; k++) {
            ans = max(ans, cycle_len(k));
        }
        cout << i << " " << j << " " << ans << "\n";
    }

    return 0;
}
