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
        long long M;
        cin >> N >> M;

        vector<long long> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];

        long long ans = -1;

        for (long long k = 0; k <= 1000000; k++) {
            long long sum = 0;
            for (int i = 0; i < N; i++) {
                sum += (A[i] ^ k);
            }
            if (sum <= M) {
                ans = k;
            } else {
                break;
            }
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
