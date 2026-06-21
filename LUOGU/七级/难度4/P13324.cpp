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

        vector<int> d(N), l(N);
        for (int i = 0; i < N; i++) cin >> d[i] >> l[i];

        int D;
        cin >> D;

        int max_reach = d[0] + l[0];

        for (int i = 1; i < N; i++) {
            if (d[i] <= max_reach) {
                max_reach = max(max_reach, d[i] + l[i]);
            }
        }

        cout << "Case #" << t << ": " << (max_reach >= D ? "YES" : "NO") << "\n";
    }

    return 0;
}
