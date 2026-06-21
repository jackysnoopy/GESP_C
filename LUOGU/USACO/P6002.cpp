#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    cin >> N >> K;
    vector<int> B(N);
    for (int i = 0; i < N; i++) cin >> B[i];
    int ans = 0;
    for (int x = 1; x <= 1000; x++) {
        int totalBuckets = 0;
        for (int i = 0; i < N; i++) {
            totalBuckets += B[i] / x;
        }
        if (totalBuckets < K / 2) break;
        vector<int> remainder;
        int used = 0;
        for (int i = 0; i < N; i++) {
            int full = B[i] / x;
            int rem = B[i] % x;
            used += full;
            if (full > 0) remainder.push_back(rem);
        }
        sort(remainder.rbegin(), remainder.rend());
        int need = K / 2;
        int extra = 0;
        for (int i = 0; i < (int)remainder.size() && used + extra < K / 2; i++) {
            if (remainder[i] > 0) extra++;
        }
        if (used + extra >= K / 2) {
            int bessie = 0;
            int bCount = min(used, K / 2);
            bessie = bCount * x;
            int elsie = K / 2;
            if (elsie <= used) {
                bessie = (used - elsie) * x;
            } else {
                bessie = 0;
            }
            ans = max(ans, bessie);
        }
    }
    cout << ans << "\n";
    return 0;
}
