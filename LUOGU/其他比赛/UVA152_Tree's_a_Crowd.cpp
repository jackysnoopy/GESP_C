#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y, z;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Point> points;
    int x, y, z;
    while (cin >> x >> y >> z && (x != 0 || y != 0 || z != 0)) {
        points.push_back({x, y, z});
    }

    vector<int> histogram(25, 0);

    for (size_t i = 0; i < points.size(); ++i) {
        double minDist = 1e9;
        for (size_t j = 0; j < points.size(); ++j) {
            if (i == j) continue;
            double dist = sqrt(pow(points[i].x - points[j].x, 2) +
                               pow(points[i].y - points[j].y, 2) +
                               pow(points[i].z - points[j].z, 2));
            minDist = min(minDist, dist);
        }
        int bucket = min((int)minDist, 24);
        histogram[bucket]++;
    }

    for (int i = 0; i < 25; ++i) {
        cout << histogram[i] << "\n";
    }

    return 0;
}
