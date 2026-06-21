#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int R, C, N;
        cin >> R >> C >> N;

        int total = R * C;
        if (N == 0 || N == total) {
            cout << "Case #" << t << ": " << (N == total ? (R-1)*C + R*(C-1) : 0) << "\n";
            continue;
        }

        int half = (total + 1) / 2;
        if (N <= half) {
            cout << "Case #" << t << ": 0\n";
        } else {
            int extra = N - half;
            int ans = 0;

            if (R == 1 || C == 1) {
                ans = extra;
            } else {
                ans = min(extra, 2 * extra - (R > 1 && C > 1 ? 1 : 0));
            }

            cout << "Case #" << t << ": " << ans << "\n";
        }
    }

    return 0;
}
