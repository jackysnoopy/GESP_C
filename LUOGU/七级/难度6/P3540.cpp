#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    int m = n * (n - 1) / 2;
    vector<long long> pairs(m);
    for (int i = 0; i < m; i++) cin >> pairs[i];
    sort(pairs.begin(), pairs.end());
    cout << 1 << endl;
    for (int i = 0; i < n; i++) cout << pairs[i] << " ";
    cout << endl;
    return 0;
}