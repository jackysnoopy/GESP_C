#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    
    vector<pair<double, double>> intervals;
    
    for (int i = 0; i < n; i++) {
        double x, y, r;
        scanf("%lf %lf %lf", &x, &y, &r);
        
        double d = sqrt(x * x + y * y);
        
        if (d <= r) {
            printf("0.000\n");
            return 0;
        }
        
        double theta = atan2(y, x);
        double phi = asin(r / d);
        
        double left = theta - phi;
        double right = theta + phi;
        
        left = max(left, 0.0);
        right = min(right, M_PI / 2);
        
        if (left < right) {
            intervals.push_back({left, right});
        }
    }
    
    sort(intervals.begin(), intervals.end());
    
    double totalBlocked = 0.0;
    double curLeft = -1, curRight = -1;
    
    for (auto& [l, r] : intervals) {
        if (l > curRight) {
            if (curRight >= 0) {
                totalBlocked += curRight - curLeft;
            }
            curLeft = l;
            curRight = r;
        } else {
            curRight = max(curRight, r);
        }
    }
    if (curRight >= 0) {
        totalBlocked += curRight - curLeft;
    }
    
    double prob = 1.0 - totalBlocked / (M_PI / 2.0);
    printf("%.3f\n", prob);
    
    return 0;
}
