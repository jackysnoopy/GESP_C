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

    sort(a.begin(), a.end());

    vector<int> result;
    int left = 0, right = n - 1;

    while (left <= right) {
        if (result.size() % 2 == 0) {
            result.push_back(a[right--]);
        } else {
            result.push_back(a[left++]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << result[i];
    }
    cout << "\n";

    return 0;
}
