#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, b;
    cin >> n >> b;

    vector<int> prices(n);
    for (int i = 0; i < n; i++) cin >> prices[i];

    sort(prices.begin(), prices.end());

    int cnt = 0;
    for (int p : prices) {
        if (b >= p) {
            b -= p;
            cnt++;
        }
    }

    cout << cnt << "\n";
    return 0;
}
