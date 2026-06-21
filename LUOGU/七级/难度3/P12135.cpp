#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 统计有多少个值大于等于k
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] >= k) {
            count++;
        }
    }

    cout << count << "\n";

    return 0;
}
