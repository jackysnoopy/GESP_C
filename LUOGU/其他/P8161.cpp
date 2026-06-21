#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    long long M;
    cin >> N >> M;
    vector<long long> A(N), B(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];
    long long lo = 0, hi = 1e18;
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;
        long long total = 0;
        for (int i = 0; i < N; i++) {
            if (A[i] >= mid) {
                long long need = (mid + A[i] - 1) / A[i];
                total += max(0LL, need - M);
            } else {
                long long need = (mid + B[i] - 1) / B[i];
                total += max(0LL, need - M);
            }
        }
        if (total <= (long long)N * M) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
    return 0;
}
