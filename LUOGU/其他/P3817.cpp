#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x;
    cin >> n >> x;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long ans = 0;
    for (int i = 1; i < n; i++) {
        long long sum = a[i-1] + a[i];
        if (sum > x) {
            long long need = sum - x;
            ans += need;
            a[i] -= need;
            if (a[i] < 0) a[i] = 0;
        }
    }
    cout << ans << endl;
    return 0;
}
