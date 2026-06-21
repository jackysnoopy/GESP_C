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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 题目要求计算数组的和
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }

    cout << sum << "\n";

    return 0;
}
