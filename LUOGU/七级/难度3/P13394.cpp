#include <iostream>
#include <vector>
using namespace std;
int main() {
    int C;
    cin >> C;
    for (int tc = 1; tc <= C; tc++) {
        int N, K, B, T;
        cin >> N >> K >> B >> T;
        vector<int> X(N), V(N);
        for (int i = 0; i < N; i++) cin >> X[i];
        for (int i = 0; i < N; i++) cin >> V[i];
        int slow = 0, swaps = 0, got = 0;
        bool impossible = false;
        for (int i = N - 1; i >= 0; i--) {
            bool canReach = (X[i] + (long long)V[i] * T >= B);
            if (canReach) {
                swaps += slow;
                got++;
                if (got >= K) break;
            } else {
                slow++;
            }
        }
        cout << "Case #" << tc << ": ";
        if (got >= K) cout << swaps << "\n";
        else cout << "IMPOSSIBLE\n";
    }
    return 0;
}
