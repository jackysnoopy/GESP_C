#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        long long C;
        cin >> N >> C;
        vector<int> a(N);
        for (int i = 0; i < N; i++) a[i] = i + 1;
        bool ok = true;
        long long remaining = C;
        for (int i = N - 1; i >= 1; i--) {
            int maxVal = N - i + 1;
            long long ci = min(remaining - (long long)(i - 1), (long long)maxVal);
            if (ci < 1) { ok = false; break; }
            remaining -= ci;
            int lo = i, hi = i + (int)ci - 1;
            while (lo < hi) { swap(a[lo-1], a[hi-1]); lo++; hi--; }
        }
        if (ok && remaining == 0) {
            cout << "Case #" << tc << ":";
            for (int x : a) cout << " " << x;
            cout << "\n";
        } else {
            cout << "Case #" << tc << ": IMPOSSIBLE\n";
        }
    }
    return 0;
}
