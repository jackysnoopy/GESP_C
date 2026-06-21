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
        int P, K, L;
        cin >> P >> K >> L;
        vector<long long> freq(L);
        for (int i = 0; i < L; i++) cin >> freq[i];
        sort(freq.rbegin(), freq.rend());
        long long ans = 0;
        int pos = 0;
        for (int key = 1; key <= K; key++) {
            for (int p = 1; p <= P && pos < L; p++, pos++) {
                ans += freq[pos] * p;
            }
        }
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
