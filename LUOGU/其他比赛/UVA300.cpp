#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Letter {
    int x1, y1, x2, y2;
};

bool cmp(const Letter& a, const Letter& b) {
    if (a.x1 == b.x1) return a.y1 > b.y1;
    return a.x1 < b.x1;
}

int lis(vector<int>& v) {
    vector<int> d;
    for (int x : v) {
        auto it = lower_bound(d.begin(), d.end(), x);
        if (it == d.end()) d.push_back(x);
        else *it = x;
    }
    return d.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n) {
        vector<Letter> letters(n);
        for (int i = 0; i < n; i++) {
            cin >> letters[i].x1 >> letters[i].y1 >> letters[i].x2 >> letters[i].y2;
            // 小红只能向东或向南走，所以起点必须在终点的左上方
            if (letters[i].x1 > letters[i].x2 || letters[i].y1 < letters[i].y2) {
                // 无法送达，交换起点和终点使其无效
                letters[i].x1 = letters[i].x2 = 0;
                letters[i].y1 = letters[i].y2 = 0;
            }
        }
        sort(letters.begin(), letters.end(), cmp);
        vector<int> ends;
        for (int i = 0; i < n; i++) {
            if (letters[i].x1 != 0 || letters[i].y1 != 0) {
                ends.push_back(letters[i].y2);
            }
        }
        cout << (int)ends.size() - lis(ends) << "\n";
    }
    return 0;
}
