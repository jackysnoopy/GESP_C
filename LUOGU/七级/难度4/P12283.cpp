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

    int ans = 0;
    for (int i = 1; i < n; i++) {
        long long diff = a[i] - a[i - 1];
        long long maxAllowed = 2 * diff;
        while (a[i] - a[i - 1] > maxAllowed) {
            ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
