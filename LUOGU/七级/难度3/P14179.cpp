#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int total = 0, cur = 0;
    for (int x : a) {
        cur += x;
        if (cur < 0) cur = 0;
        total = max(total, cur);
    }

    cout << total << "\n";
    return 0;
}
