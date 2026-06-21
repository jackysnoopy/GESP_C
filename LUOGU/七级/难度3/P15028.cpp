#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> gifts(n);
    for (int i = 0; i < n; i++) cin >> gifts[i];

    int total = 0;
    for (int g : gifts) total += g;

    cout << total / n << "\n";
    return 0;
}
