#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// [ICPC 2022 Xi'an R] Find Maximum
// Without data file.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << *max_element(a.begin(), a.end()) << "\n";
    return 0;
}
