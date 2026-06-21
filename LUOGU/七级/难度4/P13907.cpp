#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long n, k;
        cin >> n >> k;

        long long ans = 0;
        long long level = 1;
        long long nodes = 1;

        while (nodes < k) {
            ans++;
            level *= 2;
            nodes = nodes * 2 + 1;
        }

        cout << ans << "\n";
    }

    return 0;
}
