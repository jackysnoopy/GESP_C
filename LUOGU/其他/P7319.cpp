#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    long long ans = 0;
    sort(w.begin(), w.end());
    long long posSum = 0, negSum = 0;
    for (int i = 0; i < n; i++) {
        if (w[i] >= 0) posSum += w[i];
        else negSum += w[i];
    }
    ans = posSum - negSum;
    cout << ans << "\n";
    return 0;
}
