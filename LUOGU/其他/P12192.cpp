#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int a[11], b[11];
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    int total = 0;
    for (int i = 0; i < n; i++) total += min(a[i], b[i]);
    cout << total << "\n";
    return 0;
}
