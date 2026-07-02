#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        int cnt = 0;
        int ans = 0;
        while (n--) {
            int r, s, d;
            char ch;
            cin >> r >> ch >> s >> ch >> d >> ch;
            if (s <= 90) {
                cnt++;
                if (cnt <= 10) ans += r * (10 - s);
            } else {
                cnt = 0;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
