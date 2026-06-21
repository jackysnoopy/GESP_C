#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string x, y;
    cin >> x >> y;
    // f(x, z) = y means min(x[i], z[i]) = y[i] for all i.
    // For each position i:
    //   if x[i] > y[i]: z[i] = y[i] works (min(x[i], y[i]) = y[i])
    //   if x[i] == y[i]: z[i] can be any char >= y[i], use 'z'
    //   if x[i] < y[i]: impossible (min(x[i], z[i]) <= x[i] < y[i])
    string z(n, 'z');
    for (int i = 0; i < n; i++) {
        if (x[i] < y[i]) {
            cout << -1 << "\n";
            return 0;
        }
        if (x[i] > y[i]) {
            z[i] = y[i];
        }
        // x[i] == y[i]: z[i] stays 'z', min(x[i], 'z') = x[i] = y[i]. Correct.
    }
    cout << z << "\n";
    return 0;
}
