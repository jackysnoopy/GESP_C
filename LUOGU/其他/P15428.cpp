#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    long long sa = 0, sb = 0;
    for (int i = 0; i < n; i++) { cin >> a[i] >> b[i]; sa += a[i]; sb += b[i]; }
    long long diff = sa - sb;
    for (int i = 0; i < n; i++) {
        if (a[i] - b[i] <= diff) { cout << i + 1 << "\n"; return 0; }
    }
    cout << "impossible\n";
    return 0;
}
