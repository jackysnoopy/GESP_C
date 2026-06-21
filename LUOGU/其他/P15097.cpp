#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int C, N;
    cin >> C >> N;
    vector<int> T(N);
    for (int i = 0; i < N; i++) cin >> T[i];
    // Binary search on answer: can we make all wash days have temp >= mid?
    int lo = -50, hi = 50, ans = -50;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        // Try to schedule wash days so each wash day has temp >= mid
        // We must wash at least once every C+1 days
        // In each block of C+1 days, at least 1 must be wash (no coat)
        // We want all wash days to have temp >= mid
        bool ok = true;
        int pos = 0;
        while (pos < N) {
            // Must find a wash day in [pos, pos+C] with temp >= mid
            bool found = false;
            int best = pos;
            for (int j = pos; j <= min(pos + C, N - 1); j++) {
                if (T[j] >= mid) { found = true; best = j; break; }
            }
            if (!found) { ok = false; break; }
            pos = best + C + 1;
        }
        if (ok) { ans = mid; lo = mid + 1; }
        else hi = mid - 1;
    }
    cout << ans << "\n";
    return 0;
}
