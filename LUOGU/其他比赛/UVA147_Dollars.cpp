#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

using namespace std;

const int denominations[7] = {100, 50, 20, 10, 5, 2, 1};
long long dp[30001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int coin : denominations) {
        for (int amount = coin; amount <= 30000; ++amount) {
            dp[amount] += dp[amount - coin];
        }
    }

    double amount;
    while (cin >> amount && amount > 0.001) {
        int cents = static_cast<int>(amount * 100 + 0.5);
        cout << setw(6) << fixed << setprecision(2) << amount 
             << setw(17) << dp[cents] << endl;
    }

    return 0;
}
