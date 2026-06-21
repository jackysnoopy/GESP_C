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
        int N, A, B;
        cin >> N >> A >> B;

        vector<int> U(N + 1);
        for (int i = 1; i <= N; i++) cin >> U[i];

        int ans = -1;
        for (int start = N; start <= 1000; start++) {
            vector<int> have(N + 1, 0);
            have[start] = 1;

            bool possible = true;
            for (int i = start; i > 0; i--) {
                if (have[i] == 0) continue;

                if (i <= A) {
                    have[i] = 0;
                } else if (i <= B) {
                    have[i - A] += have[i];
                    have[i] = 0;
                } else {
                    have[i - A] += have[i];
                    have[i - B] += have[i];
                    have[i] = 0;
                }
            }

            for (int i = 1; i <= N; i++) {
                if (have[i] < U[i]) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                ans = start;
                break;
            }
        }

        cout << "Case #" << t << ": ";
        if (ans == -1) cout << "IMPOSSIBLE\n";
        else cout << ans << "\n";
    }

    return 0;
}
