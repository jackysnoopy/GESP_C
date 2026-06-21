#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<pair<int, pair<int, int>>> tasks(N);
    for (int i = 0; i < N; i++) {
        cin >> tasks[i].first >> tasks[i].second.first >> tasks[i].second.second;
    }

    sort(tasks.begin(), tasks.end());

    int key_count = 0;
    long long total_value = 0;

    for (int i = 0; i < N; i++) {
        if (tasks[i].second.second == 1) {
            key_count++;
            total_value += tasks[i].second.first;
        }
    }

    cout << key_count << " " << total_value << "\n";
    return 0;
}
