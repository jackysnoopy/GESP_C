#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> steps(n);
    for (int i = 0; i < n; i++) cin >> steps[i];

    int total = 0;
    for (int s : steps) total += s;

    cout << total << "\n";
    return 0;
}
