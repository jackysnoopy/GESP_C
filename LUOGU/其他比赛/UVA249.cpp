#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    
    vector<int> sector(N, 0);
    
    for (int i = 0; i < K; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        double dx = x2 - x1;
        double dy = y2 - y1;
        double len = 0;
        if (dx == 0 && dy == 0) {
            continue;
        }
        len = dx * dx + dy * dy;
        
        for (int j = 0; j < N; j++) {
            double angle1 = (2.0 * 3.14159265358979 * j) / N;
            double angle2 = (2.0 * 3.14159265358979 * (j + 1)) / N;
            
            double ex1 = cos(angle1), ey1 = sin(angle1);
            double ex2 = cos(angle2), ey2 = sin(angle2);
            
            double cross1 = (x1 * ey1 - y1 * ex1) * (x2 * ey1 - y2 * ex1);
            double cross2 = (x1 * ey2 - y1 * ex2) * (x2 * ey2 - y2 * ex2);
            
            if (cross1 <= 0 && cross2 <= 0) {
                sector[j]++;
            } else if (cross1 > 0 || cross2 > 0) {
                double cross3 = (ex1 * dy - ey1 * dx) * (ex2 * dy - ey2 * dx);
                if (cross3 <= 0) {
                    sector[j]++;
                }
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        cout << i + 1 << ": " << sector[i] << endl;
    }
    
    return 0;
}
