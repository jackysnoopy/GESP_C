#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int P, A, B;
    while (cin >> P >> A >> B && (P || A || B)) {
        vector<pair<int, int>> solutions;
        for (int x = 0; x * A <= P; x++) {
            int rem = P - x * A;
            if (rem % B == 0) {
                solutions.push_back({x, rem / B});
            }
        }
        for (auto& sol : solutions) {
            cout << sol.first << " " << sol.second << endl;
        }
        if (solutions.empty()) cout << "None" << endl;
    }
    return 0;
}
