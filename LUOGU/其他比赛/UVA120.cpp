#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void flip(vector<int>& pancakes, int pos) {
    int left = 0, right = pos;
    while (left < right) {
        swap(pancakes[left], pancakes[right]);
        left++;
        right--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;

        vector<int> pancakes;
        int num = 0;
        bool inNumber = false;

        for (char c : line) {
            if (c == ' ') {
                if (inNumber) {
                    pancakes.push_back(num);
                    num = 0;
                    inNumber = false;
                }
            } else {
                num = num * 10 + (c - '0');
                inNumber = true;
            }
        }
        if (inNumber) pancakes.push_back(num);

        int n = pancakes.size();
        vector<int> sorted_pancakes = pancakes;
        sort(sorted_pancakes.begin(), sorted_pancakes.end());

        for (int i = 0; i < n; i++) {
            cout << pancakes[i];
            if (i < n - 1) cout << " ";
        }
        cout << "\n";

        vector<int> flips;

        for (int target = 0; target < n; target++) {
            int maxIdx = target;
            for (int i = target; i < n; i++) {
                if (pancakes[i] > pancakes[maxIdx]) {
                    maxIdx = i;
                }
            }

            if (maxIdx == target) continue;

            if (maxIdx != n - 1) {
                flip(pancakes, maxIdx);
                flips.push_back(n - maxIdx);
            }

            flip(pancakes, n - target - 1);
            flips.push_back(n - target);
        }

        flips.push_back(0);

        for (int i = 0; i < (int)flips.size(); i++) {
            cout << flips[i];
            if (i < (int)flips.size() - 1) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
