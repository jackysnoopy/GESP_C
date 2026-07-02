#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double W, D;

    while (cin >> W >> D) {
        if (W < D) swap(W, D);

        int count1 = (int)(W / D);

        int count2 = count1;
        bool staggered = true;

        while (true) {
            double horizontalSpace;
            if (staggered) {
                horizontalSpace = W - D / 2.0;
            } else {
                horizontalSpace = W;
            }

            if (horizontalSpace < D) break;

            int countInRow = (int)(horizontalSpace / D);
            if (countInRow == 0) break;

            count2 += countInRow;
            staggered = !staggered;

            double verticalSpace = D * sqrt(3.0) / 2.0 * (count2 > count1 ? 1 : 0);
            if (verticalSpace > D) break;
        }

        cout << count1 << " max" << endl;
    }

    return 0;
}
