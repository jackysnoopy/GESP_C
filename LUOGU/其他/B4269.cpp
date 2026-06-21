#include <iostream>
using namespace std;

long long gcd(long long a, long long b) {
    while (b) { long long t = b; b = a % b; a = t; }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 10; i++) {
        long long a, b;
        cin >> a >> b;
        long long g = gcd(a, b);
        cout << (a / g + b / g - 1) * g << "\n";
    }
    return 0;
}
