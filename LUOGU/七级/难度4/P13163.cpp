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
        int N, P;
        cin >> N >> P;

        vector<int> R(N);
        for (int i = 0; i < N; i++) cin >> R[i];

        vector<vector<int>> Q(N, vector<int>(P));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                cin >> Q[i][j];
            }
        }

        for (int i = 0; i < N; i++) {
            sort(Q[i].begin(), Q[i].end());
        }

        int ans = 0;
        vector<int> idx(N, 0);

        while (true) {
            bool all_valid = true;
            int min_serving = 0;
            int max_serving = 1e9;

            for (int i = 0; i < N; i++) {
                if (idx[i] >= P) {
                    all_valid = false;
                    break;
                }
                int q = Q[i][idx[i]];
                int low = (q * 10 + 9 * R[i] - 1) / (9 * R[i]);
                int high = (q * 10) / (11 * R[i]);
                if (low > high) {
                    all_valid = false;
                    break;
                }
                min_serving = max(min_serving, low);
                max_serving = min(max_serving, high);
            }

            if (!all_valid || min_serving > max_serving) {
                int min_idx = 0;
                for (int i = 1; i < N; i++) {
                    if (idx[i] < P && Q[i][idx[i]] < Q[min_idx][idx[min_idx]]) {
                        min_idx = i;
                    }
                }
                if (idx[min_idx] < P) {
                    idx[min_idx]++;
                } else {
                    break;
                }
            } else {
                ans++;
                for (int i = 0; i < N; i++) idx[i]++;
            }
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
