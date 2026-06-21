#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double C, F, X;
    cin >> C >> F >> X;

    // Cookie Clicker Alpha：饼干点击者
    double rate = 2.0;
    double time = 0.0;

    while (true) {
        double current_time = X / rate;
        double new_time = C / rate + X / (rate + F);
        
        if (current_time <= new_time) {
            time += current_time;
            break;
        } else {
            time += C / rate;
            rate += F;
        }
    }

    cout << fixed << setprecision(7) << time << "\n";
    return 0;
}
