#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long A, B, C;
    cin >> A >> B >> C;
    long long ans = 0;
    long long vals[3] = {A, B, C};
    sort(vals, vals + 3);
    if (vals[0] == vals[1] || vals[1] == vals[2]) {
        cout << 0 << "\n";
        return 0;
    }
    if (vals[1] != A && vals[1] != C) {
        cout << 0 << "\n";
        return 0;
    }
    long long best = 1000000000LL;
    for (int mask = 0; mask < 8; mask++) {
        long long na = A, nb = B, nc = C;
        if (mask & 1) na--;
        if (mask & 2) nb--;
        if (mask & 4) nc--;
        if (na <= 0 || nb <= 0 || nc <= 0) continue;
        long long vals2[3] = {na, nb, nc};
        sort(vals2, vals2 + 3);
        if (vals2[0] == vals2[1] || vals2[1] == vals2[2]) {
            best = min(best, (long long)__builtin_popcount(mask));
        } else if (vals2[1] != na && vals2[1] != nc) {
            best = min(best, (long long)__builtin_popcount(mask));
        }
    }
    cout << best << "\n";
    return 0;
}
