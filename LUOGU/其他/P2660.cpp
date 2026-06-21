#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long x;
    cin >> x;
    // Fence perimeter x. Maximize area of rectangle.
    // Area = a * b where 2*(a+b) = x, a+b = x/2
    // Max a*b when a = b = x/4
    long long s = x / 2;
    long long a = s / 2;
    long long b = s - a;
    cout << a * b << "\n";
    return 0;
}
