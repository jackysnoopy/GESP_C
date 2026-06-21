#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        unsigned int s, t;
        cin >> n >> s >> t;
        if (s == t) { cout << 0 << "\n"; continue; }
        unsigned int full = (1U << n) - 1;
        unsigned int ans = s ^ t;
        cout << ans << "\n";
    }
    return 0;
}
