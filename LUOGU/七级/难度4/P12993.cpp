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
        int N;
        long long K;
        cin >> N >> K;

        long long total = (long long)N * N;

        if (K >= total - 1) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }

        int shortcuts = 0;
        long long cur = 1;

        while (cur < total) {
            if (cur + 1 == total) {
                break;
            }

            long long next = cur + 1;
            long long max_next = min((long long)total, cur + 2 * (N - 1));

            if (max_next > next && shortcuts < K - (total - 1 - K)) {
                next = max_next;
                shortcuts++;
            }

            cur = next;
        }

        cout << "Case #" << t << ": " << shortcuts << "\n";
    }

    return 0;
}
