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
        int N, M, K;
        cin >> N >> M >> K;
        const int THRESH = 4000;
        vector<bool> dp(THRESH + 1, false);
        dp[min(N, THRESH)] = true;
        bool has_large = (N > THRESH);
        string answer(M, ' ');
        bool possible = true;
        for (int i = 0; i < M && possible; i++) {
            vector<int> moves(K);
            for (int j = 0; j < K; j++) cin >> moves[j];
            int max_odd = 0, max_even = 0;
            for (int a : moves) {
                if (a % 2 == 1) max_odd = max(max_odd, a);
                else max_even = max(max_even, a);
            }
            bool all_above_odd = (max_odd == 0);
            bool all_above_even = (max_even == 0);
            if (!all_above_odd) {
                all_above_odd = true;
                if (has_large && THRESH < max_odd) all_above_odd = false;
                if (all_above_odd) {
                    for (int m = 0; m <= min(THRESH, max_odd); m++) {
                        if (dp[m]) { all_above_odd = false; break; }
                    }
                }
            }
            if (!all_above_even) {
                all_above_even = true;
                if (has_large && THRESH < max_even) all_above_even = false;
                if (all_above_even) {
                    for (int m = 0; m <= min(THRESH, max_even); m++) {
                        if (dp[m]) { all_above_even = false; break; }
                    }
                }
            }
            if (all_above_odd) {
                answer[i] = 'E';
            } else if (all_above_even) {
                answer[i] = 'O';
            } else {
                possible = false;
                break;
            }
            vector<bool> new_dp(THRESH + 1, false);
            bool new_has_large = false;
            for (int m = 0; m <= THRESH; m++) {
                if (!dp[m]) continue;
                for (int a : moves) {
                    if (answer[i] == 'E') {
                        if (a % 2 == 0) {
                            int nm = m + a;
                            if (nm > THRESH) new_has_large = true;
                            else new_dp[nm] = true;
                        } else {
                            int nm = m - a;
                            if (nm > 0) {
                                if (nm > THRESH) new_has_large = true;
                                else new_dp[nm] = true;
                            }
                        }
                    } else {
                        if (a % 2 == 1) {
                            int nm = m + a;
                            if (nm > THRESH) new_has_large = true;
                            else new_dp[nm] = true;
                        } else {
                            int nm = m - a;
                            if (nm > 0) {
                                if (nm > THRESH) new_has_large = true;
                                else new_dp[nm] = true;
                            }
                        }
                    }
                }
            }
            if (has_large) new_has_large = true;
            dp = new_dp;
            has_large = new_has_large;
        }
        if (!possible) {
            cout << -1 << "\n";
        } else {
            for (int i = 0; i < M; i++) {
                if (i) cout << " ";
                cout << (answer[i] == 'E' ? "Even" : "Odd");
            }
            cout << "\n";
        }
    }
    return 0;
}
