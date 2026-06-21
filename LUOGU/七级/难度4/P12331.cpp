#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<long long> K(M), B(M);
    for (int i = 0; i < M; i++) {
        cin >> K[i] >> B[i];
    }

    vector<int> X(M, 0);
    priority_queue<pair<long long, int>> pq;

    for (int i = 0; i < M; i++) {
        long long gain = K[i] + B[i];
        if (gain > 0) pq.push({gain, i});
    }

    long long ans = 0;
    for (int p = 0; p < N && !pq.empty(); p++) {
        auto [gain, idx] = pq.top();
        pq.pop();
        if (gain <= 0) break;
        ans += gain;
        X[idx]++;
        long long next_gain = K[idx] * (2 * X[idx] + 1) + B[idx];
        if (next_gain > 0) {
            pq.push({next_gain, idx});
        }
    }

    cout << ans << "\n";
    return 0;
}
