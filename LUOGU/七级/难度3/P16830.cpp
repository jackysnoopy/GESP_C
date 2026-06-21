#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> towers(n);
    for (int i = 0; i < n; i++) cin >> towers[i];

    int maxDist = 0;
    for (int i = 1; i < n; i++) {
        maxDist = max(maxDist, abs(towers[i] - towers[i-1]));
    }

    cout << maxDist << "\n";
    return 0;
}
