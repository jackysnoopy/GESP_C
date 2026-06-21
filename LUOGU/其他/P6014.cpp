#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> cnt(11, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i] % 10]++;
    }
    int total = 0;
    for (int i = 0; i < n; i++) total += a[i];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int s2 = (a[i] + a[j]) % 10;
            if (s2 == 0) s2 = 10;
            int rem = total - a[i] - a[j];
            if (rem % 10 == 0) {
                cout << s2 << "\n";
                return 0;
            }
        }
    }
    cout << "0\n";
    return 0;
}
