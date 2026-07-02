#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        vector<double> prices(n);
        for (int i = 0; i < n; i++) cin >> prices[i];
        double maxProfit = 0;
        int buyDay = -1, sellDay = -1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double profit = prices[j] - prices[i];
                if (profit > maxProfit) {
                    maxProfit = profit;
                    buyDay = i;
                    sellDay = j;
                }
            }
        }
        if (maxProfit > 0) {
            cout << fixed << setprecision(2);
            cout << maxProfit << "\n";
        } else {
            cout << "0.00\n";
        }
    }
    return 0;
}
