#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int L, N, M;
    cin >> L >> N >> M;
    vector<int> d(N + 2);
    d[0] = 0; d[N + 1] = L;
    for (int i = 1; i <= N; i++) cin >> d[i];
    int lo = 1, hi = L;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        int removed = 0, last = 0;
        for (int i = 1; i <= N + 1; i++) {
            if (d[i] - d[last] < mid) removed++;
            else last = i;
        }
        if (removed <= M) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
    return 0;
}
