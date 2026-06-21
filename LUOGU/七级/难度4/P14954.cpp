#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, a, b, c;
        cin >> n >> a >> b >> c;

        string s;
        cin >> s;

        int count5 = 0, count2 = 0, count0 = 0;
        for (char ch : s) {
            if (ch == '5') count5++;
            else if (ch == '2') count2++;
            else count0++;
        }

        count5 += a;
        count2 += b;
        count0 += c;

        int ans = min({count5, count2, count0});
        cout << ans << "\n";
    }

    return 0;
}
