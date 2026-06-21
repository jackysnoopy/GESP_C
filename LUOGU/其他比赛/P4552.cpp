#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long pos = 0, neg = 0;
    for (int i = 1; i < n; i++) {
        long long d = a[i] - a[i-1];
        if (d > 0) pos += d;
        else neg -= d;
    }
    cout << max(pos, neg) << "\n" << abs(pos - neg) + 1 << "\n";
    return 0;
}
