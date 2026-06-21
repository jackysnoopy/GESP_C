#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];
    vector<int> diff(n);
    for (int i = 0; i < n; i++) diff[i] = A[i] - B[i];
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return diff[i] > diff[j];
    });
    long long ans = 0;
    for (int i = 0; i < a; i++) ans += A[idx[i]];
    for (int i = a; i < n; i++) ans += B[idx[i]];
    cout << ans << "\n";
    return 0;
}
