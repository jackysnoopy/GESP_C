#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    int total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total += a[i];
    }
    sort(a.rbegin(), a.rend());
    int half = total / 2;
    int sum = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        ans = a[i];
        if (sum > half) {
            break;
        }
    }
    cout << ans << "\n";
    return 0;
}
