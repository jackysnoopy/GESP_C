#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    set<int> s(a.begin(), a.end());

    int mex = 0;
    while (s.count(mex)) mex++;

    cout << mex << "\n";
    return 0;
}
