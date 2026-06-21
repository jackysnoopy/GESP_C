#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

bool isLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int daysInMonth(int y, int m) {
    int d[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && isLeap(y)) return 29;
    return d[m];
}

int dayOfWeek(int y, int m, int d) {
    if (m < 3) { m += 12; y--; }
    int K = y % 100, J = y / 100;
    int h = (d + (13*(m+1))/5 + K + K/4 + J/4 + 5*J) % 7;
    return (h + 6) % 7; // 0=周日,1=周一,...,6=周六
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int w, y, m;
    while (cin >> w >> y >> m) {
        int first = dayOfWeek(y, m, 1);
        int ndays = daysInMonth(y, m);
        // 打印标题
        cout << "     " << setw(2) << m << '/' << y << '\n';
        cout << " Sun Mon Tue Wed Thu Fri Sat\n";
        // 计算第一天在日历中的位置
        int pos = (first - w + 7) % 7;
        for (int i = 0; i < pos; ++i) cout << "    ";
        for (int d = 1; d <= ndays; ++d) {
            cout << setw(4) << d;
            if ((pos + d) % 7 == 0) cout << '\n';
        }
        if ((pos + ndays) % 7 != 0) cout << '\n';
        cout << '\n';
    }
    return 0;
}
