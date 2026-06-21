#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N, X;
        cin >> N >> X;
        vector<int> S(N);
        for (int i = 0; i < N; i++) cin >> S[i];
        sort(S.begin(), S.end());
        int ans = 0;
        int lo = 0, hi = N - 1;
        while (lo <= hi) {
            if (lo == hi) { ans++; break; }
            if (S[lo] + S[hi] <= X) {
                lo++; hi--; ans++;
            } else {
                hi--; ans++;
            }
        }
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
