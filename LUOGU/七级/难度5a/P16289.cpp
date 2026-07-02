#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> w(n), c(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < n; i++) cin >> c[i];
    long long cost = 0;
    long long bat = 0;
    for (int i = 0; i < n; i++) {
        long long need = w[i];
        while (bat > 0 && need > 0) {
            bat--;
            need--;
        }
        if (need > 0) {
            cost += need * c[i];
        }
        long long space = k - bat;
        if (space > 0) {
            cost += space * c[i];
            bat = k;
        }
    }
    cout << cost << "\n";
    return 0;
}
