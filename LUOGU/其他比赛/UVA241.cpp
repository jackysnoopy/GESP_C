#include <iostream>
#include <string>
#include <map>
using namespace std;

struct Cube {
    int face[6];
    void rotateFront() {
        int t = face[0];
        face[0] = face[3];
        face[3] = face[5];
        face[5] = face[1];
        face[1] = t;
    }
    void rotateRight() {
        int t = face[2];
        face[2] = face[3];
        face[3] = face[4];
        face[4] = face[1];
        face[1] = t;
    }
};

int main() {
    string line;
    int dataset = 0;
    while (getline(cin, line) && line != "0") {
        dataset++;
        Cube cube;
        for (int i = 0; i < 6; i++) cube.face[i] = i;
        
        for (char c : line) {
            if (c == 'F') cube.rotateFront();
            else if (c == 'R') cube.rotateRight();
        }
        
        cout << "Pattern " << dataset << ": ";
        for (int i = 0; i < 6; i++) cout << cube.face[i];
        cout << endl;
    }
    return 0;
}
