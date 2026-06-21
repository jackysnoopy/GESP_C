#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Rearrange or count something based on k
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n && j < i+k; j++) {
            if (a[i] > a[j]) ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}
