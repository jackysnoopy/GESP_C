#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> p(n + 1), pos(n + 1);
    for (int i = 1; i <= n; i++) { cin >> p[i]; pos[p[i]] = i; }
    int k = n;
    while (k > 1 && pos[k - 1] < pos[k]) k--;
    cout << k - 1 << "\n";
    return 0;
}
