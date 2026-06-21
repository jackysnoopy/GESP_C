#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> planks(n);
    for (int i = 0; i < n; i++) cin >> planks[i];

    cout << *min_element(planks.begin(), planks.end()) << "\n";
    return 0;
}
