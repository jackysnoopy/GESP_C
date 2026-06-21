#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N, M;
        cin >> N >> M;

        vector<pair<long long, long long>> sets(N);
        for (int i = 0; i < N; i++) cin >> sets[i].first >> sets[i].second;

        vector<long long> students(M);
        for (int i = 0; i < M; i++) cin >> students[i];

        set<long long> available;
        for (auto& [a, b] : sets) {
            for (long long i = a; i <= b; i++) available.insert(i);
        }

        cout << "Case #" << t << ":";
        for (int i = 0; i < M; i++) {
            long long best = -1;
            long long best_diff = 1e18;

            for (long long d = 0; d <= 1e18; d++) {
                if (available.count(students[i] - d)) {
                    best = students[i] - d;
                    break;
                }
                if (available.count(students[i] + d)) {
                    best = students[i] + d;
                    break;
                }
            }

            available.erase(best);
            cout << " " << best;
        }
        cout << "\n";
    }

    return 0;
}
