#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Video {
    int t, d, idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Video> videos(n);
    for (int i = 0; i < n; i++) {
        cin >> videos[i].t >> videos[i].d;
        videos[i].idx = i + 1;
    }
    
    // Sort by deadline
    sort(videos.begin(), videos.end(), [](const Video& a, const Video& b) {
        return a.d < b.d;
    });
    
    // Greedy: schedule videos in order of deadline
    // For each video, try to schedule it as late as possible
    // but before its deadline
    
    vector<int> schedule; // schedule[i] = day when video i starts
    long long current_time = 0;
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (current_time + videos[i].t <= videos[i].d) {
            // Can schedule this video
            schedule.push_back(current_time + 1); // 1-indexed day
            current_time += videos[i].t;
            count++;
        }
    }
    
    cout << count << endl;
    for (int i = 0; i < count; i++) {
        cout << videos[i].idx << " " << schedule[i] << endl;
    }
    
    return 0;
}
