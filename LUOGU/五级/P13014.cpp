#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // 计算 D = gcd(a[1]-a[0], a[2]-a[0], ..., a[n-1]-a[0])
    int D = 0;
    for (int i = 1; i < n; i++) {
        D = gcd(D, a[i] - a[0]);
    }
    
    // 处理每个询问
    int i=1;
    while (q--) {

        cout << gcd(a[0] + i, D) << endl;
        i++;
    }
    
    return 0;
}