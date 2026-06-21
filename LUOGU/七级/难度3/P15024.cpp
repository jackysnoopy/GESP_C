#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> costs(n);
    for (int i = 0; i < n; i++) cin >> costs[i];

    sort(costs.begin(), costs.end());
    cout << costs[0] << "\n";
    return 0;
}
