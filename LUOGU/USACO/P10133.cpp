#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<long long> a(N + 1);
    for (int i = 1; i <= N; i++) cin >> a[i];
    long long ans = 0, cur = 0;
    for (int i = 1; i <= N; i++) {
        a[i] += cur;
        if (a[i] != 0) {
            ans += abs(a[i]);
            cur -= a[i];
        }
    }
    cout << ans << "\n";
    return 0;
}
