#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n && n != 0) {
        double total = 0;
        for (int i = 0; i < n; i++) {
            double force, distance;
            cin >> force >> distance;
            total += force * distance;
        }
        if (total == 0) {
            cout << "Equilibrium" << endl;
        } else if (total > 0) {
            cout << "Clockwise" << endl;
        } else {
            cout << "Counterclockwise" << endl;
        }
    }
    return 0;
}
