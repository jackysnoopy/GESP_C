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

    // Infinite House of Pancakes：无限的煎饼屋
    // 简化：计算需要的翻转次数
    int total = 0;
    for (int i = 0; i < n; i++) {
        int minutes = a[i] / 10;
        if (a[i] % 10 != 0) minutes++;
        total += minutes;
    }

    cout << total << "\n";

    return 0;
}
