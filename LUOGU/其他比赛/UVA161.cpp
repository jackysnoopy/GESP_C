#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

int main() {
    int h, m, s;
    while (cin >> h >> m >> s && (h || m || s)) {
        int total = h * 3600 + m * 60 + s;
        int cnt = 0;
        for (int i = 0; i < 3600; i++) {
            int t = total + i;
            if (t % 2 == 0 && t % 3 == 0 && t % 5 == 0 && t % 7 == 0 && t % 11 == 0) {
                cnt++;
            }
        }
        printf("%02d:%02d:%02d\n", cnt / 3600, (cnt % 3600) / 60, cnt % 60);
    }
    return 0;
}
