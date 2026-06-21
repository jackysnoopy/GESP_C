#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Student {
    int chn, math, eng, idx;
    int total() const { return chn + math + eng; }
    int cm_sum() const { return chn + math; }
    int cm_max() const { return max(chn, math); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<Student> stu(N);
    for (int i = 0; i < N; i++) {
        cin >> stu[i].chn >> stu[i].math >> stu[i].eng;
        stu[i].idx = i;
    }
    sort(stu.begin(), stu.end(), [](const Student &a, const Student &b) {
        if (a.total() != b.total()) return a.total() > b.total();
        if (a.cm_sum() != b.cm_sum()) return a.cm_sum() > b.cm_sum();
        if (a.cm_max() != b.cm_max()) return a.cm_max() > b.cm_max();
        return false;  // equal means no preference
    });
    vector<int> rank(N);
    int current_rank = 1;
    for (int i = 0; i < N; i++) {
        if (i > 0 && stu[i].total() == stu[i-1].total() 
            && stu[i].cm_sum() == stu[i-1].cm_sum()
            && stu[i].cm_max() == stu[i-1].cm_max()) {
            // Same rank as previous student
            rank[stu[i].idx] = current_rank;
        } else {
            current_rank = i + 1;
            rank[stu[i].idx] = current_rank;
        }
    }
    for (int i = 0; i < N; i++) cout << rank[i] << "\n";
    return 0;
}
