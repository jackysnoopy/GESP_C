#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> power(n);
    for (int i = 0; i < n; i++) cin >> power[i];

    int maxPower = *max_element(power.begin(), power.end());
    int minPower = *min_element(power.begin(), power.end());

    cout << maxPower - minPower << "\n";
    return 0;
}
