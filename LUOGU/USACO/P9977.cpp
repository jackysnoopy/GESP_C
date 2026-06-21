#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    long long M, K;
    cin >> N >> M >> K;
    vector<pair<long long, long long>> cows(N);
    for (int i = 0; i < N; i++) cin >> cows[i].first >> cows[i].second;
    sort(cows.begin(), cows.end(), greater<pair<long long, long long>>());
    
    struct Entry { long long weight; long long count; };
    vector<Entry> towers; // sorted by weight ascending
    long long empty = M;
    long long ans = 0;
    
    for (int i = 0; i < N; i++) {
        long long w = cows[i].first;
        long long cnt = cows[i].second;
        
        // Find eligible towers (weight >= w+K) from back
        long long avail = 0;
        int cut = (int)towers.size();
        for (int j = (int)towers.size() - 1; j >= 0; j--) {
            if (towers[j].weight >= w + K) {
                avail += towers[j].count;
                cut = j;
            } else break;
        }
        
        long long place = min(cnt, avail);
        ans += place;
        cnt -= place;
        
        long long on_empty = min(cnt, empty);
        ans += on_empty;
        cnt -= on_empty;
        empty -= on_empty;
        
        // Rebuild
        vector<Entry> new_towers(towers.begin(), towers.begin() + cut);
        
        long long remaining = place;
        for (int j = (int)towers.size() - 1; j >= cut; j--) {
            long long take = min(towers[j].count, remaining);
            towers[j].count -= take;
            remaining -= take;
            if (towers[j].count > 0) {
                new_towers.push_back(towers[j]);
            }
        }
        
        long long new_count = place + on_empty;
        if (new_count > 0) {
            // Insert at front (since w is smaller than existing weights)
            if (!new_towers.empty() && new_towers[0].weight == w) {
                new_towers[0].count += new_count;
            } else {
                new_towers.insert(new_towers.begin(), {w, new_count});
            }
        }
        
        towers = new_towers;
    }
    
    cout << ans << "\n";
    return 0;
}
