#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long K;
    int N;
    if (!(cin >> K >> N)) return 0;
    vector<int> X(N);
    for (int i = 0; i < N; ++i) cin >> X[i];
    for (int i = 0; i < N; ++i) {
        long long x = X[i];
        long long y = 0;
        while (true) {
            long long up = y + 1;
            long long down = max(0LL, y - 1);
            long long reach = up * (up + 1) / 2 + y * y + down * (down + 1) / 2;
            if (reach >= K) break;
            ++y;
        }
        long long T = 0;
        long long pos = 0, cur = y;
        while (pos < K) {
            ++T;
            if (cur < x) ++cur;
            else if (cur > x) --cur;
            pos += cur;
        }
        cout << T << '\n';
    }
    return 0;
}
