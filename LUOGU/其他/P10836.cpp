#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    string a, b;
    cin >> a >> b;
    int ca = 0, cb = 0;
    for (char c : a) if (c == '#') ca++;
    for (char c : b) if (c == '#') cb++;
    int ai = 0, bi = 0;
    for (int i = 1; i <= m; i++) {
        char ch = (char)('a' + (i - 1) % 26);
        if (ai < ca) {
            a[ai] = ch;
            int pos = 0;
            for (int j = 0; j < n; j++) {
                if (a[j] == '#') { pos = j; break; }
            }
            ai++;
        } else {
            int pos = 0;
            for (int j = 0; j < n; j++) {
                if (b[j] == '#') { pos = j; break; }
            }
            b[pos] = ch;
            bi++;
        }
    }
    cout << a << "\n";
    return 0;
}
