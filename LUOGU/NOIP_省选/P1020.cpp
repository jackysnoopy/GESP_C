#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> h;
    int x;
    while (cin >> x) h.push_back(x);
    int n = h.size();
    vector<int> piles;
    for (int i = 0; i < n; i++) {
        auto it = upper_bound(piles.begin(), piles.end(), h[i], greater<int>());
        if (it == piles.end()) piles.push_back(h[i]);
        else *it = h[i];
    }
    cout << piles.size() << "\n";
    piles.clear();
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(piles.begin(), piles.end(), h[i]);
        if (it == piles.end()) piles.push_back(h[i]);
        else *it = h[i];
    }
    cout << piles.size() << endl;
    return 0;
}
