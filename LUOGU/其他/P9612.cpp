#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    if (!(cin >> N >> K)) return 0;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];
    sort(a.begin(), a.end(), greater<int>());
    long long ans = 0;
    for (int i = 0; i < K; ++i) ans += a[i];
    cout << ans << '\n';
    return 0;
}
