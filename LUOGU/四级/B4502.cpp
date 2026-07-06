#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Box {
    int id, total, mx, mn;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, k;
    cin >> N >> k;
    
    vector<Box> boxes(N);
    for (int i = 0; i < N; i++) {
        boxes[i].id = i + 1;
        boxes[i].mn = 1e9;
        boxes[i].mx = -1;
        boxes[i].total = 0;
        for (int j = 0; j < k; j++) {
            int p;
            cin >> p;
            boxes[i].total += p;
            boxes[i].mx = max(boxes[i].mx, p);
            boxes[i].mn = min(boxes[i].mn, p);
        }
    }
    
    sort(boxes.begin(), boxes.end(), [](const Box& a, const Box& b) {
        if (a.total != b.total) return a.total < b.total;
        if (a.mx != b.mx) return a.mx < b.mx;
        if (a.mn != b.mn) return a.mn < b.mn;
        return a.id < b.id;
    });
    
    for (int i = 0; i < N; i++)
        cout << boxes[i].id << (i + 1 < N ? " " : "\n");
    
    return 0;
}