#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> stations(n);
    for (int i = 0; i < n; i++) cin >> stations[i];

    int total = 0;
    for (int i = 1; i < n; i++) {
        total += abs(stations[i] - stations[i-1]);
    }

    cout << total << "\n";
    return 0;
}
