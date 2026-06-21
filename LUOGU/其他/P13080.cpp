#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> xs(n), ys(n);
    for (int i = 0; i < n; i++) cin >> xs[i] >> ys[i];
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    long long mx = xs[n / 2], my = ys[n / 2];
    if (n % 2 == 0) mx = xs[n / 2 - 1];
    if (n % 2 == 0) my = ys[n / 2 - 1];
    cout << mx << " " << my << endl;
    return 0;
}
