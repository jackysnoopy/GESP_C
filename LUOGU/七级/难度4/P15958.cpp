#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> P(N);
    for (int i = 0; i < N; i++) cin >> P[i];

    vector<int> result(N, 0);
    for (int i = 0; i < N; i++) {
        if (P[i] != 0) result[i] = P[i];
    }

    vector<pair<int, int>> constraints(K);
    for (int i = 0; i < K; i++) {
        cin >> constraints[i].first >> constraints[i].second;
    }

    for (int i = 0; i < N; i++) {
        if (P[i] == 0) {
            result[i] = -1;
        }
    }

    for (int i = 0; i < N; i++) {
        cout << result[i];
        if (i < N - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}
