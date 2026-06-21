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

    set<int> s;
    int duplicates = 0;
    for (int x : a) {
        if (s.count(x)) duplicates++;
        else s.insert(x);
    }

    cout << duplicates << "\n";
    return 0;
}
