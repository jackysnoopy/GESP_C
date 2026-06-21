#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end(), [](const string& x, const string& y) {
        return x + y > y + x;
    });
    string result;
    for (int i = 0; i < n; i++) result += a[i];
    cout << result << "\n";
    return 0;
}
