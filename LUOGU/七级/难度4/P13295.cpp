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
        int N, P;
        cin >> N >> P;

        long long total = 1LL << N;
        long long guaranteed = 0;
        long long possible = 0;

        for (long long team = 0; team < total; team++) {
            bool can_win = true;
            for (long long other = team + 1; other < total; other++) {
                if (__builtin_popcountll(team & other) > 0) {
                    can_win = false;
                    break;
                }
            }
            if (can_win) guaranteed = team;
        }

        for (long long team = total - 1; team >= 0; team--) {
            bool can_win = false;
            for (long long other = 0; other < total; other++) {
                if (other != team && __builtin_popcountll(team & other) == 0) {
                    can_win = true;
                    break;
                }
            }
            if (can_win) {
                possible = team;
                break;
            }
        }

        cout << "Case #" << t << ": " << guaranteed << " " << possible << "\n";
    }

    return 0;
}
