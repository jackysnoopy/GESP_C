#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    long long posSum = 0, negSum = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] >= 0) posSum += v[i];
        else negSum += v[i];
    }
    cout << posSum - negSum << "\n";
    return 0;
}
