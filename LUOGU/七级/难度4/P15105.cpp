#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long P, H;
    cin >> N >> P >> H;

    vector<char> type(N);
    vector<long long> value(N);

    int attack_count = 0;
    for (int i = 0; i < N; i++) {
        cin >> type[i];
        if (type[i] == '!') {
            value[i] = 0;
            attack_count++;
        } else {
            cin >> value[i];
        }
    }

    if (attack_count == 0) {
        cout << "*\n";
        return 0;
    }

    long long power = P;
    int turns = 0;
    long long health = H;

    while (health > 0) {
        for (int i = 0; i < N; i++) {
            if (type[i] == '*') {
                power *= value[i];
            } else if (type[i] == '+') {
                power += value[i];
            } else {
                health -= power;
                turns++;
                if (health <= 0) {
                    cout << turns << "\n";
                    return 0;
                }
            }
        }
    }

    cout << "*\n";
    return 0;
}
