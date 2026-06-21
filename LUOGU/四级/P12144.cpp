#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<double> starts, ends;
    
    for (int i = 0; i < n; i++) {
        double x, y, r;
        cin >> x >> y >> r;
        
        // 从原点看这个圆，计算被遮挡的角度范围
        // 圆心到原点的距离
        double d = sqrt(x * x + y * y);
        // 圆心的角度
        double center = atan2(y, x);
        // 圆的半角
        double half = asin(r / d);
        
        double s = center - half;
        double e = center + half;
        
        // 转换到 [0, pi/2] 范围
        // 如果整个区间在 [0, pi/2] 内
        if (e <= M_PI / 2 && s >= 0) {
            starts.push_back(s);
            ends.push_back(e);
        } else if (s < 0 && e > 0) {
            starts.push_back(0);
            ends.push_back(e);
        } else if (s < M_PI / 2 && e > M_PI / 2) {
            starts.push_back(s);
            ends.push_back(M_PI / 2);
        }
    }
    
    // 合并区间，计算被覆盖的总角度
    vector<pair<double, double>> intervals;
    for (int i = 0; i < (int)starts.size(); i++) {
        intervals.push_back({starts[i], ends[i]});
    }
    
    sort(intervals.begin(), intervals.end());
    
    double covered = 0;
    double cur_s = -1, cur_e = -1;
    for (int i = 0; i < (int)intervals.size(); i++) {
        if (intervals[i].first > cur_e) {
            if (cur_e > cur_s) covered += cur_e - cur_s;
            cur_s = intervals[i].first;
            cur_e = intervals[i].second;
        } else {
            cur_e = max(cur_e, intervals[i].second);
        }
    }
    if (cur_e > cur_s) covered += cur_e - cur_s;
    
    double total = M_PI / 2;
    double prob = (total - covered) / total;
    
    cout << fixed << setprecision(3) << prob << endl;
    return 0;
}
