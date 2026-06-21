#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int m, k, t1, t2;
        cin >> m >> k >> t1 >> t2;

        vector<long long> ans(m + 1);
        long long time = 0;
        int wool = 1;
        int pos = 0;

        for (int d = 1; d <= m; d++) {
            while (pos < d) {
                if (wool > 0) {
                    pos++;
                    wool--;
                    time += t1;
                } else {
                    time += t2;
                    wool++;
                }
            }
            ans[d] = time;
            wool++;
        }

        for (int i = 1; i <= m; i++) {
            if (i > 1) cout << " ";
            cout << ans[i];
        }
        cout << "\n";
    }

    return 0;
}
