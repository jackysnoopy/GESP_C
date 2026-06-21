#include <iostream>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int cnt = 1;
    long long cur = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (cur + a > m) { cnt++; cur = a; }
        else cur += a;
    }
    cout << cnt << "\n";
    return 0;
}
