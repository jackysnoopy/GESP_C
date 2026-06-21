#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        unsigned long long n;
        cin >> n;
        int cnt = 0;
        while (n > 1) {
            if (n % 2 == 0) {
                n /= 2;
            } else {
                cnt++;
                if ((n + 1) / 2 % 2 == 0) n = (n + 1) / 2;
                else n = (n - 1) / 2;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}
