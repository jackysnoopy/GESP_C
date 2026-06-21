#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> water(n);
    for (int i = 0; i < n; i++) cin >> water[i];

    int minWater = *min_element(water.begin(), water.end());
    cout << minWater << "\n";
    return 0;
}
