#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

int n;
vector<string> vars;

void generateCode(int depth, vector<string>& sorted) {
    if (depth == n) {
        for (int i = 0; i < n; i++) cout << "  ";
        cout << "writeln(" << sorted[0];
        for (int i = 1; i < n; i++) cout << ", " << sorted[i];
        cout << ")\n";
        return;
    }
    string var = vars[depth];
    if (depth == 0) {
        sorted.push_back(var);
        generateCode(1, sorted);
        sorted.pop_back();
        return;
    }
    function<void(int)> go = [&](int pos) {
        for (int j = 0; j < depth; j++) cout << "  ";
        if (pos < depth) {
            cout << "if " << sorted[pos] << " < " << var << " then\n";
            go(pos + 1);
            for (int j = 0; j < depth; j++) cout << "  ";
            cout << "else\n";
        }
        sorted.insert(sorted.begin() + pos, var);
        generateCode(depth + 1, sorted);
        sorted.erase(sorted.begin() + pos);
    };
    go(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        vars.resize(n);
        for (int i = 0; i < n; i++) cin >> vars[i];
        cout << "program sort(input, output);\n";
        cout << "var\n";
        for (int i = 0; i < n; i++) {
            cout << "  " << vars[i];
            if (i < n - 1) cout << ",";
        }
        cout << " : integer;\n";
        cout << "begin\n";
        cout << "  writeln(";
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << ", ";
            cout << vars[i];
        }
        cout << ")\n";
        vector<string> sorted;
        generateCode(0, sorted);
        cout << "end.\n";
        if (T > 0) cout << "\n";
    }
    return 0;
}
