#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    cin >> N >> Q;
    vector<long long> T(N + 1);
    for (int i = 1; i <= N; i++) cin >> T[i];
    long long sum = 0;
    for (int i = 1; i < N; i++) sum += abs(T[i] - T[i+1]);
    while (Q--) {
        int l, r; long long v;
        cin >> l >> r >> v;
        if (l > 1) {
            long long old = abs(T[l-1] - T[l]);
            long long nw = abs(T[l-1] - (T[l] + v));
            sum += nw - old;
        }
        if (r < N) {
            long long old = abs(T[r] - T[r+1]);
            long long nw = abs((T[r] + v) - T[r+1]);
            sum += nw - old;
        }
        T[l] += v;
        if (l != r) T[r] += v;
        cout << sum << "\n";
    }
    return 0;
}
