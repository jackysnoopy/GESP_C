#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N, T, x;
    cin >> N >> T >> x;
    long long max_inf = min(N, x + 2 * T);
    long long min_inf = min(N, x + T);
    cout << max_inf << " " << min_inf << "\n";
    return 0;
}
