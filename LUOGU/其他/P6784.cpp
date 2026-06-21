#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    // Walk from 1 to n, can step +1 or +2
    // Count number of ways
    if (n == 1) { cout << 1 << "\n"; return 0; }
    long long a = 1, b = 1;
    for (int i = 2; i <= n; i++) {
        long long c = a + b;
        a = b;
        b = c;
    }
    cout << b << "\n";
    return 0;
}
