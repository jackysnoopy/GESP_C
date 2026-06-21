#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M, S, T;
    cin >> M >> S >> T;
    int maxDist = 0;
    for (int f = 0; f <= T; f++) {
        int need_mp = 10 * f;
        int r = 0;
        if (need_mp > M) r = (need_mp - M + 3) / 4;
        if (f + r > T) continue;
        int d = 60 * f + 17 * (T - f - r);
        if (d > maxDist) maxDist = d;
    }
    if (maxDist >= S) {
        int answer = T;
        for (int f = 0; f <= T; f++) {
            int need_mp = 10 * f;
            int r = 0;
            if (need_mp > M) r = (need_mp - M + 3) / 4;
            if (f + r > T) continue;
            int run_needed = 0;
            if (S > 60 * f) run_needed = (S - 60 * f + 16) / 17;
            int total = f + r + run_needed;
            if (total <= T) answer = min(answer, total);
        }
        cout << "Yes\n" << answer << "\n";
    } else {
        cout << "No\n" << maxDist << "\n";
    }
    return 0;
}
