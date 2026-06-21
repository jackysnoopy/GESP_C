#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> houses(n);
    for (int i = 0; i < n; i++) cin >> houses[i];

    int maxH = *max_element(houses.begin(), houses.end());
    cout << maxH << "\n";
    return 0;
}
