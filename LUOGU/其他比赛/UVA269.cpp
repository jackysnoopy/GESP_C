#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    int size = (int)pow(2, n);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((i & j) == 0) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
