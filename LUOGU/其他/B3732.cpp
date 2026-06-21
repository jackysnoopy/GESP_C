#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long R;
    cin >> n >> R;
    vector<long long> a(n);
    long long cur = R;
    for (int i = 0; i < n; i++) {
        a[i] = (cur % 100) + 1;
        cur = (cur * 6807 + 2831) % 201701;
    }
    sort(a.begin(), a.end());
    long long sum = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        ans += sum;
    }
    cout << ans << "\n";
    return 0;
}
