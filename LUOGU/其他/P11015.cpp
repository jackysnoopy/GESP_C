#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        if (x == y) { cout << 0 << "\n"; continue; }
        cout << 1 << "\n";
    }
    return 0;
}
