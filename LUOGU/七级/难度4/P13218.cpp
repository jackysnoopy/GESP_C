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
        long long N;
        cin >> N;

        long long ans = 0;
        long long cur = 1;

        while (cur < N) {
            string s = to_string(cur);
            string rev = s;
            reverse(rev.begin(), rev.end());
            long long r = stoll(rev);

            if (r > cur && r <= N) {
                cur = r;
                ans++;
            } else {
                cur++;
                ans++;
            }
        }

        cout << "Case #" << t << ": " << ans + 1 << "\n";
    }

    return 0;
}
