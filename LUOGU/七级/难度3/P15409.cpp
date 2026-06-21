#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long lcm = 1;
    for (int x : a) {
        lcm = lcm / gcd(lcm, (long long)x) * x;
    }

    cout << lcm << "\n";
    return 0;
}
