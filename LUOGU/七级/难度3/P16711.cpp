#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> journey(n);
    for (int i = 0; i < n; i++) cin >> journey[i];

    int total = 0;
    for (int j : journey) total += j;

    cout << total << "\n";
    return 0;
}
