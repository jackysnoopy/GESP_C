#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        vector<int> scores(n);
        for (int i = 0; i < n; i++) cin >> scores[i];
        sort(scores.begin(), scores.end());
        double sum = 0;
        for (int i = 1; i < n - 1; i++) sum += scores[i];
        double avg = sum / (n - 2);
        cout << fixed << setprecision(2) << avg << "\n";
    }
    return 0;
}
