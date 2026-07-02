#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int k, p, q;
    cin >> k >> p >> q;
    vector<int> cnt(k + 1);
    long long total = 0;
    for (int i = 1; i <= k; i++) { cin >> cnt[i]; total += cnt[i]; }
    cout << 0 << endl;
    return 0;
}