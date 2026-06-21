#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long cur = 1;
    long long mn = 1;
    for (int i = 0; i < n; i++) {
        cur += a[i];
        if (cur < 1) {
            mn += (1 - cur);
            cur = 1;
        }
    }
    cout << mn << "\n";
    return 0;
}
