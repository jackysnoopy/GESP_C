#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    // Precompute next occurrence for each position
    vector<int> next_pos(N, N);
    unordered_map<int, int> last;
    for (int i = N - 1; i >= 0; i--) {
        if (last.count(a[i])) next_pos[i] = last[a[i]];
        last[a[i]] = i;
    }
    // Optimal offline caching (Belady's algorithm)
    // When cache is full and we need to evict, remove the item whose next access is furthest
    unordered_map<int, int> cache; // value -> next access position
    priority_queue<pair<int, int>> pq; // (next_access, value)
    int misses = 0;
    for (int i = 0; i < N; i++) {
        if (cache.count(a[i])) {
            // Cache hit: update next access
            cache[a[i]] = next_pos[i];
            pq.push({next_pos[i], a[i]});
        } else {
            // Cache miss
            misses++;
            if ((int)cache.size() == M) {
                // Evict: remove entries with stale next_access
                while (!pq.empty()) {
                    auto top = pq.top();
                    if (cache.count(top.second) && cache[top.second] == top.first) {
                        // Valid entry, evict it
                        cache.erase(top.second);
                        pq.pop();
                        break;
                    }
                    pq.pop(); // stale entry, skip
                }
            }
            cache[a[i]] = next_pos[i];
            pq.push({next_pos[i], a[i]});
        }
    }
    cout << misses << "\n";
    return 0;
}
