#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    int a1, d, x;
    cin >> a1 >> d >> x;

    vector<int> a(k + 1);
    a[1] = a1;
    for (int i = 2; i <= k; i++) {
        a[i] = (a[i - 1] - d) ^ x;
    }

    long long total = n + m;
    long long black = n;

    long long ans = 1;
    for (int i = 1; i <= k; i++) {
        long long groups = a[i];
        long long black_per_group = black / groups;
        ans = ans * black_per_group % 998244353;
        black = black_per_group;
    }

    cout << ans << "\n";
    return 0;
}
