#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N, K;
        cin >> N >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        sort(P.begin(), P.end());
        P.erase(unique(P.begin(), P.end()), P.end());
        int m = P.size();
        vector<int> gaps;
        if (m == 0) {
            cout << "Case #" << tc << ": " << fixed << setprecision(9) << 1.0 << "\n";
            continue;
        }
        if (m == 1) {
            int cov = K - 1;
            cout << "Case #" << tc << ": " << fixed << setprecision(9) << (double)cov / K << "\n";
            continue;
        }
        gaps.push_back(P[0] - 1);
        gaps.push_back(K - P[m-1]);
        for (int i = 0; i + 1 < m; i++)
            gaps.push_back((P[i+1] - P[i]) / 2);
        sort(gaps.rbegin(), gaps.rend());
        int best = max(gaps[0], (m >= 2 ? (gaps[0] + (gaps.size() > 1 ? gaps[1] : 0)) : gaps[0]));
        // Also consider full gap (two tickets in same gap)
        int fullGap = P[0] - 1;
        fullGap = max(fullGap, K - P[m-1]);
        for (int i = 0; i + 1 < m; i++)
            fullGap = max(fullGap, P[i+1] - P[i] - 1);
        best = max(best, fullGap);
        // Also: two largest one-ticket coverages
        int sum2 = gaps[0];
        if (gaps.size() > 1) sum2 += gaps[1];
        best = max(best, sum2);
        cout << "Case #" << tc << ": " << fixed << setprecision(9) << (double)best / K << "\n";
    }
    return 0;
}
