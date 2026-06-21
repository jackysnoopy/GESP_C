#include <iostream>
#include <vector>
#include <set>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    set<int> s;
    for (int i = 0; i < n; i++) { cin >> a[i]; s.insert(a[i]); }
    int mex = 0;
    while (s.count(mex)) mex++;
    cout << mex << "\n";
    return 0;
}
