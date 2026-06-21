#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> herbs(n);
    for (int i = 0; i < n; i++) cin >> herbs[i];

    int maxVal = *max_element(herbs.begin(), herbs.end());
    cout << maxVal << "\n";
    return 0;
}
