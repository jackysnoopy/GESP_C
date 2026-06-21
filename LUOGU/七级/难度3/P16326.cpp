#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> stars(n);
    for (int i = 0; i < n; i++) cin >> stars[i];

    int maxBright = *max_element(stars.begin(), stars.end());
    cout << maxBright << "\n";
    return 0;
}
