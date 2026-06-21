#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b, p;
    cin >> a >> b >> p;
    
    cout << a << "^" << b << " mod " << p << "=";
    
    long long ans = 1 % p;
    a %= p;
    while (b) {
        if (b & 1) ans = ans * a % p;
        a = a * a % p;
        b >>= 1;
    }
    
    cout << ans << "\n";
    return 0;
}