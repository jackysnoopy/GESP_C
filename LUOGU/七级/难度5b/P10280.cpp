#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll k;
    cin >> n >> k;
    string a, b;
    cin >> a >> b;

    vector<ll> pa, pb;
    for (int i = 0; i < n; i++) {
        if (a[i] == '1') pa.push_back(i);
        if (b[i] == '1') pb.push_back(i);
    }

    ll totalDist = 0;
    for (int i = 0; i < (int)pa.size(); i++) {
        totalDist += abs(pa[i] - pb[i]);
    }

    ll ans = (totalDist + k - 1) / k;
    cout << ans << "\n";
    return 0;
}
