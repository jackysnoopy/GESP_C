#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        long long M, R;
        int N;
        cin >> M >> R >> N;
        vector<long long> X(N);
        for (int i = 0; i < N; i++) cin >> X[i];
        long long covered = 0;
        int ans = 0;
        int i = 0;
        bool impossible = false;
        while (covered < M) {
            long long best = covered;
            while (i < N && X[i] - R <= covered) {
                best = max(best, X[i] + R);
                i++;
            }
            if (best <= covered) {
                impossible = true;
                break;
            }
            covered = best;
            ans++;
        }
        cout << "Case #" << tc << ": ";
        if (impossible) cout << "IMPOSSIBLE";
        else cout << ans;
        cout << "\n";
    }
    return 0;
}
