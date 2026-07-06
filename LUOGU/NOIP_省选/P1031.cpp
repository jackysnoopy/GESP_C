#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long a[101];
    long long sum = 0;
    for (int i = 1; i <= n; i++) { cin >> a[i]; sum += a[i]; }
    long long avg = sum / n;
    int ans = 0;
    for (int i = 1; i < n; i++) {
        long long diff = a[i] - avg;
        a[i + 1] += diff;
        if (diff != 0) ans++;
    }
    cout << ans << endl;
    return 0;
}
