#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int j = 0;
    int matched = 0;
    for (int i = 0; i < n; i++) {
        while (j < n && b[j] >= a[i]) j++;
        if (j < n) { matched++; j++; }
    }
    cout << n - matched << "\n";
    return 0;
}
