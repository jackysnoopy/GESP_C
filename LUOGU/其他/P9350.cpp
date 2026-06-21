#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<pair<long long,long long>> residents(n);
    for (int i = 0; i < n; i++) cin >> residents[i].first >> residents[i].second;
    cout << n << "\n";
    return 0;
}
