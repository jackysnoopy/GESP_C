#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    while (b) { int t = a % b; a = b; b = t; }
    return a;
}

// [蓝桥杯 2022 国 A] 最大公约数
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    int g = a[0];
    for (int i = 1; i < n; i++) g = gcd(g, a[i]);
    
    if (g == 1) cout << n << "\n";
    else cout << "0\n";
    return 0;
}
