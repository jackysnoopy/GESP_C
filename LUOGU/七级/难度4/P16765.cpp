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
        cin >> N;

        vector<long long> E(N), R(N);
        for (int i = 0; i < N; i++) cin >> E[i] >> R[i];

        long long total_time = 0;
        for (int i = 0; i < N; i++) total_time += E[i];

        bool can_be_indefinite = false;
        int min_remove = 0;

        for (int i = 0; i < N; i++) {
            if (total_time - E[i] >= R[i]) {
                can_be_indefinite = true;
                break;
            }
        }

        if (can_be_indefinite) {
            cout << "Case #" << t << ": INDEFINITELY 0\n";
        } else {
            cout << "Case #" << t << ": " << total_time << " 0\n";
        }
    }

    return 0;
}
