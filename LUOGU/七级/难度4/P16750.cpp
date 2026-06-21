#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N, K;
        cin >> N >> K;

        vector<string> strings(N);
        for (int i = 0; i < N; i++) cin >> strings[i];

        sort(strings.begin(), strings.end());

        long long ans = 0;
        int count = 0;

        for (int i = 0; i < N; i++) {
            int common = 0;
            if (i > 0) {
                int j = i - 1;
                while (j >= 0 && count < K - 1) {
                    int len = min(strings[i].size(), strings[j].size());
                    int k = 0;
                    while (k < len && strings[i][k] == strings[j][k]) k++;
                    common = max(common, k);
                    j--;
                    count++;
                }
            }
            ans += common;
            if (count >= K - 1) count = 0;
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
