#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    char h1, h2, m1, m2;
    while (cin >> h1 >> m1 >> h2 >> m2) {
        if (h1 == '0' && m1 == '0' && h2 == '0' && m2 == '0') break;
        int hour = (h1 - '0') * 10 + (m1 - '0');
        int minute = (h2 - '0') * 10 + (m2 - '0');
        double h_angle = (hour % 12) * 30.0 + minute * 0.5;
        double m_angle = minute * 6.0;
        double diff = fabs(h_angle - m_angle);
        if (diff > 180.0) diff = 360.0 - diff;
        printf("%.0f\n", diff);
    }
    return 0;
}
