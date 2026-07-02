#include <iostream>
#include <algorithm>
using namespace std;

int pos[9];
int target[9];
int emptyPos;

void findEmpty() {
    for (int i = 0; i < 9; i++)
        if (pos[i] == 0) { emptyPos = i; return; }
}

int findPiece(int val) {
    for (int i = 0; i < 9; i++)
        if (pos[i] == val) return i;
    return -1;
}

void move(int from, int to) {
    pos[to] = pos[from];
    pos[from] = 0;
    emptyPos = from;
}

int main() {
    int k;
    while (cin >> k) {
        for (int i = 0; i < 9; i++) cin >> target[i];
        for (int i = 0; i < 9; i++) pos[i] = 0;
        pos[k] = target[k];
        findEmpty();
        int moves = 0;
        for (int i = 0; i < 9 && moves <= 100; i++) {
            if (pos[i] == target[i]) continue;
            int p = findPiece(target[i]);
            while (p != i) {
                if (emptyPos == i) {
                    move(p, i);
                    p = emptyPos;
                } else if (emptyPos == target[p]) {
                    move(p, emptyPos);
                    p = emptyPos;
                } else {
                    move(emptyPos, target[p]);
                }
                moves++;
                if (moves > 100) break;
            }
        }
        cout << moves << endl;
    }
    return 0;
}
