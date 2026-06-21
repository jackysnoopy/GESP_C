#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<long long> T(N), Z(N);
    for (int i = 0; i < N; i++) { cin >> T[i] >> Z[i]; }
    // Total liquid is fixed. Minimize non-empty glasses = maximize empty glasses.
    // Empty a glass means redistributing its liquid to others.
    // Sort by Z[i] (capacity), try to fill glasses with largest capacity first.
    vector<int> idx(N);
    for (int i = 0; i < N; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) { return Z[a] > Z[b]; });
    vector<long long> cur(N);
    for (int i = 0; i < N; i++) cur[i] = T[idx[i]];
    long long leftover = 0;
    vector<long long> ans(N);
    int emptyCount = 0;
    for (int i = 0; i < N; i++) {
        long long cap = Z[idx[i]];
        long long avail = cur[i] + leftover;
        if (avail >= cap) {
            ans[idx[i]] = cap;
            leftover = avail - cap;
        } else {
            ans[idx[i]] = avail;
            leftover = 0;
        }
    }
    for (int i = 0; i < N; i++) if (ans[i] == 0) emptyCount++;
    cout << emptyCount << "\n";
    for (int i = 0; i < N; i++) cout << ans[i] << (i + 1 < N ? " " : "\n");
    return 0;
}
