#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int h, w;
    cin >> h >> w;
    int x1, x2, y1, y2;
    cin >> x1 >> x2 >> y1 >> y2;
    vector<string> s(h);
    for (int i = 0; i < h; i++) cin >> s[i];
    for (int i = x1 - 1; i <= x2 - 1; i++) {
        cout << s[i].substr(y1 - 1, y2 - y1 + 1) << "\n";
    }
    return 0;
}
