#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> h(N);
        for (int i = 0; i < N; i++) cin >> h[i];
        long long ans = 0;
        bool impossible = false;
        for (int i = 1; i < N - 1; i += 2) {
            int mx = max(h[i-1], h[i+1]);
            if (h[i] < mx) {
                ans += mx - h[i];
                h[i] = mx;
            }
        }
        if (N % 2 == 0) {
            int mx = h[N-2];
            if (h[N-1] < mx) {
                ans += mx - h[N-1];
                h[N-1] = mx;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
