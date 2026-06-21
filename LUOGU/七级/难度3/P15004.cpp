#include <iostream>
#include <numeric>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    int g = gcd(a, b);
    cout << g << "\n";
    return 0;
}
