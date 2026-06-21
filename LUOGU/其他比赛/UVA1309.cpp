#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

static bool is_leap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

static int days_in_month(int y, int m) {
    static const int md[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && is_leap(y)) return 29;
    return md[m - 1];
}

static int day_of_week(int y, int m, int d) {
    int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    if (m < 3) --y;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int w, y, m;
    bool first = true;
    while (cin >> w >> y >> m) {
        if (!first) cout << '\n';
        first = false;
        int days = days_in_month(y, m);
        int dow = day_of_week(y, m, 1);
        int start = ((dow - w) % 7 + 7) % 7;

        cout << "Sun Mon Tue Wed Thu Fri Sat\n";
        for (int i = 0; i < start; ++i) cout << "    ";
        for (int d = 1; d <= days; ++d) {
            cout << setw(3) << d << ' ';
            if ((start + d) % 7 == 0) cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}
