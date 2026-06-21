#include <iostream>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    cin >> n;
    int cnt = 0;
    for (long long i = 1; i <= n; i++) {
        string s = to_string(i);
        if (s.find("2026") != string::npos) cnt++;
    }
    cout << cnt << "\n";
    return 0;
}
