#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, b, c, d, e, f, g, h, k, x, y;
    cin >> a >> b >> c >> d >> e >> f >> g >> h >> k >> x >> y;
    // Initial LP = d + x. Try using loveca = 0,1,2,... until we can reach y pt
    for (int loveca = 0; loveca <= 20000; loveca++) {
        long long lp = (long long)d + x + (long long)loveca * c;
        long long lpmax = c;
        long long exp = f;
        long long expmax = e;
        long long pt = 0;
        // Play songs as long as possible
        while (lp >= b) {
            lp -= b;
            pt += a;
            exp += g;
            if (exp >= expmax) {
                lp += lpmax + h;
                lpmax += h;
                exp -= expmax;
                expmax += k;
            }
        }
        if (pt >= y) {
            cout << loveca << "\n";
            return 0;
        }
    }
    return 0;
}
