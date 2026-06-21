#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, b;
    cin >> n >> a >> b;
    vector<long long> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    long long lo = 0, hi = 5e14;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        long long need = 0;
        for (int i = 0; i < n; i++) {
            long long rem = w[i] - mid * a;
            if (rem > 0) {
                need += (rem + b - 1) / b;
            }
        }
        if (need <= mid) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}
