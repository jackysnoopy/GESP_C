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
        double V, X;
        cin >> N >> V >> X;

        vector<double> R(N), C(N);
        for (int i = 0; i < N; i++) cin >> R[i] >> C[i];

        double total_rate = 0;
        double weighted_sum = 0;

        for (int i = 0; i < N; i++) {
            total_rate += R[i];
            weighted_sum += R[i] * C[i];
        }

        if (total_rate == 0 || abs(weighted_sum / total_rate - X) > 1e-9) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
        } else {
            double time = V / total_rate;
            cout << "Case #" << t << ": " << fixed << setprecision(7) << time << "\n";
        }
    }

    return 0;
}
