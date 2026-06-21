#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> scores(n);
    for (int i = 0; i < n; i++) cin >> scores[i];

    int maxScore = *max_element(scores.begin(), scores.end());
    int minScore = *min_element(scores.begin(), scores.end());

    cout << maxScore - minScore << "\n";
    return 0;
}
