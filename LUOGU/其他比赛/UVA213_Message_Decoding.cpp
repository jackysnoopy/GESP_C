#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string header;
    getline(cin, header);

    while (true) {
        string lenStr;
        getline(cin, lenStr);
        if (lenStr.empty() || lenStr == "0") break;

        int msgLen = 0;
        for (char c : lenStr) msgLen = msgLen * 10 + (c - '0');

        string msg;
        getline(cin, msg);

        int pos = 0;
        while (pos < msgLen) {
            int codeLen = 0;
            if (pos + 3 > msgLen) break;
            for (int i = 0; i < 3; i++) {
                codeLen = codeLen * 2 + (msg[pos + i] - '0');
            }
            pos += 3;

            if (codeLen == 0) {
                break;
            }

            while (pos < msgLen) {
                int val = 0;
                if (pos + codeLen > msgLen) break;
                for (int i = 0; i < codeLen; i++) {
                    val = val * 2 + (msg[pos + i] - '0');
                }
                pos += codeLen;

                int total = (1 << codeLen) - 1;
                if (val == total) break;

                int idx = val - (1 << codeLen) + 1 + total;
                if (idx < (int)header.size()) {
                    cout << header[idx];
                }
            }
        }
        cout << "\n";
    }

    return 0;
}
