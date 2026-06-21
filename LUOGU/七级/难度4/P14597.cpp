#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> result;
    result.push_back(a[0]);

    for (int i = 1; i < n; i++) {
        if (result.back() <= a[i]) {
            result.push_back(a[i]);
        } else {
            result.back() += a[i];
        }
    }

    cout << result.size() << "\n";
    for (int i = 0; i < (int)result.size(); i++) {
        if (i) cout << " ";
        cout << result[i];
    }
    cout << "\n";

    return 0;
}
