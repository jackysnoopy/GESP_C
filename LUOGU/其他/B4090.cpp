#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long w;
    int n;
    cin >> w >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    sort(x.begin(), x.end());
    int ans = 0;
    long long rem = w;
    for (int i = 0; i < n; i++) {
        if (rem >= x[i]) {
            rem -= x[i];
            ans++;
        } else break;
    }
    cout << ans << "\n";
    return 0;
}
