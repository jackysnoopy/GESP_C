#include <iostream>
#include <algorithm>
using namespace std;
struct Apple { int h, c; };
bool cmp(const Apple& a, const Apple& b) { return a.c < b.c; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s, a, b;
    cin >> n >> s >> a >> b;
    Apple app[5001];
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> app[cnt].h >> app[cnt].c;
        if (app[cnt].h <= a + b) cnt++;
    }
    sort(app, app + cnt, cmp);
    int ans = 0;
    for (int i = 0; i < cnt; i++) {
        if (s >= app[i].c) { s -= app[i].c; ans++; }
        else break;
    }
    cout << ans << endl;
    return 0;
}
