#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> cities(n);
    for (int i = 0; i < n; i++) cin >> cities[i];

    int minVal = *min_element(cities.begin(), cities.end());
    int maxVal = *max_element(cities.begin(), cities.end());

    cout << maxVal - minVal << "\n";
    return 0;
}
