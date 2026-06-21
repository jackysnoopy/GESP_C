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

        vector<pair<int, int>> levels(N);
        for (int i = 0; i < N; i++) cin >> levels[i].first >> levels[i].second;

        sort(levels.begin(), levels.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });

        int stars = 0;
        int games = 0;
        vector<bool> done(N, false);

        while (true) {
            bool found = false;
            for (int i = 0; i < N; i++) {
                if (!done[i] && stars >= levels[i].second) {
                    stars += (done[i] ? 1 : 2);
                    done[i] = true;
                    games++;
                    found = true;
                    break;
                }
            }
            if (found) continue;

            for (int i = 0; i < N; i++) {
                if (!done[i] && stars >= levels[i].first) {
                    stars += 1;
                    done[i] = true;
                    games++;
                    found = true;
                    break;
                }
            }
            if (!found) break;
        }

        bool all_done = true;
        for (int i = 0; i < N; i++) {
            if (!done[i]) {
                all_done = false;
                break;
            }
        }

        cout << "Case #" << t << ": ";
        if (all_done) cout << games << "\n";
        else cout << "Too Bad\n";
    }

    return 0;
}
