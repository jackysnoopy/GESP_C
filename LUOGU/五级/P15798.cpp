#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long L, R;
    cin >> L >> R;
    
    int ans = 0;
    for (long long a = 1; a <= R; a *= 2) {
        for (long long b = a; b <= R; b *= 5) {
            if (b >= L) ans++;
        }
    }
    
    cout << ans << '\n';
    return 0;
}