#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string res;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (s == "<bs>") {
            if (!res.empty()) res.pop_back();
        } else {
            res += s;
        }
    }
    cout << res << "\n";
    return 0;
}
