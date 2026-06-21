#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) ans -= n - i + 1;
        else ans += n - i + 1;
    }

    cout << abs(ans) << "\n";
    return 0;
}
