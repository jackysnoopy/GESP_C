#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> distances(n);
    for (int i = 0; i < n; i++) cin >> distances[i];

    int total = 0;
    for (int d : distances) total += d;

    cout << total << "\n";
    return 0;
}
