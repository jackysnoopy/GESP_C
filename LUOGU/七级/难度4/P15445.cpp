#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    while (Q--) {
        long long x, y, z;
        cin >> x >> y >> z;

        bool found = false;
        for (long long a = 0; a <= min(x, z / 2); a++) {
            long long b = x ^ a;
            if (b == a) continue;
            if (abs(a - b) <= y && a + b <= z) {
                found = true;
                break;
            }
        }

        cout << (found ? "YES" : "NO") << "\n";
    }

    return 0;
}
