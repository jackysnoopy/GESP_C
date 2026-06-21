#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> pages(n);
    for (int i = 0; i < n; i++) cin >> pages[i];

    int total = 0;
    for (int p : pages) total += p;

    cout << total << "\n";
    return 0;
}
