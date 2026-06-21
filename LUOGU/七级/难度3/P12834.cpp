#include <iostream>
#include <string>
using namespace std;
int main() {
    int A, B, C;
    cin >> A >> B >> C;
    if (A == 0 && B == 0) { cout << (C == 0 ? "" : "-1") << "\n"; return 0; }
    if (A == 0) {
        if (C != 0) { cout << "-1\n"; return 0; }
        cout << string(B, 'Q') << "\n"; return 0;
    }
    if (B == 0) {
        if (C != 0) { cout << "-1\n"; return 0; }
        cout << string(A, 'L') << "\n"; return 0;
    }
    int minC = 1, maxC = 2 * min(A, B);
    if (A == B) maxC--;
    if (C < minC || C > maxC) { cout << "-1\n"; return 0; }
    int blocks = C + 1;
    int lBlocks = (blocks + 1) / 2;
    int qBlocks = blocks / 2;
    if (lBlocks > A || qBlocks > B) { cout << "-1\n"; return 0; }
    string result;
    int extraL = A - lBlocks;
    int extraQ = B - qBlocks;
    int lastQBlock = 2 * qBlocks - 1;
    for (int b = 0; b < blocks; b++) {
        if (b % 2 == 0) {
            int cnt = 1;
            if (b == 0) cnt += extraL;
            result += string(cnt, 'L');
        } else {
            int cnt = 1;
            if (b == lastQBlock) cnt += extraQ;
            result += string(cnt, 'Q');
        }
    }
    cout << result << "\n";
    return 0;
}
