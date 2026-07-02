#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string add(string a, string b) {
    string res;
    int carry = 0;
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        res += (char)(sum % 10 + '0');
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    while (cin >> a >> b) {
        int len1 = a.size(), len2 = b.size();
        int maxWidth = max(len1, len2);

        vector<string> partials;
        for (int i = len2 - 1; i >= 0; i--) {
            string partial;
            int d = b[i] - '0';
            int carry = 0;
            for (int j = len1 - 1; j >= 0; j--) {
                int prod = (a[j] - '0') * d + carry;
                partial += (char)(prod % 10 + '0');
                carry = prod / 10;
            }
            if (carry) partial += (char)(carry + '0');
            reverse(partial.begin(), partial.end());
            int zeros = len2 - 1 - i;
            partial += string(zeros, '0');
            partials.push_back(partial);
        }

        string result = "0";
        for (auto& p : partials) result = add(result, p);

        int outputWidth = max(maxWidth, (int)result.size());

        for (int i = 0; i < (int)partials.size(); i++) {
            cout << string(outputWidth - partials[i].size(), ' ') << partials[i] << "\n";
            if (i == 0) {
                cout << string(outputWidth - len2, ' ') << b << "\n";
            }
        }
        cout << string(outputWidth, '-') << "\n";
        cout << result << "\n\n";
    }
    return 0;
}
