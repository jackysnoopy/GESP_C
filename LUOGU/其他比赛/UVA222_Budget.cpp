#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseno = 0;
    double budget, cost;
    int n;

    while (cin >> budget >> cost >> n && (budget != 0 || cost != 0 || n != 0)) {
        cout << "Data Set #" << ++caseno << "\n";
        cout << "  budget is " << fixed << setprecision(2) << budget << "\n";

        double monthly = budget * (1.0 - cost / 100.0);

        double total = 0;
        int months = 0;
        while (total < budget && months < n) {
            total += monthly;
            months++;
        }

        if (total >= budget) {
            cout << "  sufficient funds after " << months << " monthly payments\n";
        } else {
            cout << "  insufficient funds after " << months << " monthly payments\n";
        }
        cout << "\n";
    }

    return 0;
}
