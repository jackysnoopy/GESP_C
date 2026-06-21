#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ull = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    if (n == 0) { cout << 1 << '\n'; return 0; }
    if (n == 1) { cout << 1 << '\n'; return 0; }
    if (n == 2) { cout << 2 << '\n'; return 0; }
    
    ull a = 1, b = 1, c = 2;
    for (int i = 3; i <= n; i++) {
        ull d = a + b + c;
        a = b;
        b = c;
        c = d;
    }
    cout << c << '\n';
    
    return 0;
}
