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

        vector<int> S(N), E(N), L(N);
        for (int i = 0; i < N; i++) cin >> S[i] >> E[i] >> L[i];

        long long ans = 0;
        for (int i = 0; i < N; i++) {
            ans += max(0, E[i]);
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
