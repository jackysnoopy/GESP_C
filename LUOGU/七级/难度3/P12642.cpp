#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    ll prev = a[0], ops = 0;
    for (int i = 1; i < n; i++) {
        ll cur = a[i];
        while (cur < prev) { cur *= 2; ops++; }
        prev = cur;
    }
    cout << ops << "\n";
    return 0;
}
