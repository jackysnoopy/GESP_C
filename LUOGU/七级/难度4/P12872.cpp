#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    long long ans = 0;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            ans += nums[i].size();
        } else {
            string prev = nums[i - 1];
            string curr = nums[i];

            int zeros_needed = 0;
            bool found = false;

            for (int len = prev.size(); len <= 20; len++) {
                string padded = curr;
                while (padded.size() < len) padded = "0" + padded;
                if (padded > prev) {
                    zeros_needed = len - curr.size();
                    found = true;
                    break;
                }
            }

            if (found) {
                ans += zeros_needed;
                nums[i] = curr;
                for (int j = 0; j < zeros_needed; j++) nums[i] = "0" + nums[i];
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
