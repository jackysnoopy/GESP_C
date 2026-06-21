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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Assimilation：排序后找中位数
    sort(a.begin(), a.end());

    if (n % 2 == 1) {
        cout << a[n / 2] << "\n";
    } else {
        cout << (a[n / 2 - 1] + a[n / 2]) / 2 << "\n";
    }

    return 0;
}
