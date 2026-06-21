#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> speeds(n);
    for (int i = 0; i < n; i++) cin >> speeds[i];

    int maxSpeed = *max_element(speeds.begin(), speeds.end());
    cout << maxSpeed * m << "\n";
    return 0;
}
