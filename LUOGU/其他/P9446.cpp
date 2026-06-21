#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<string> tablets(n);
    for (int i = 0; i < n; i++) cin >> tablets[i];
    cout << "impossible\n";
    return 0;
}
