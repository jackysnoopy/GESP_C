#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    double t0, t1, f0, f1, pit_time, fuel_time;
    scanf("%d%lf%lf%lf%lf%lf%lf", &n, &t0, &t1, &f0, &f1, &pit_time, &fuel_time);
    
    // 使用动态规划或二分
    // 这里简化处理
    
    double min_time = 1e18;
    double best_fuel = 0;
    int best_stops = 0;
    
    // 尝试不同的初始油量
    for (int fuel = 0; fuel <= 1000; fuel++) {
        double f = fuel / 10.0;
        double time = 0;
        double current_fuel = f;
        int stops = 0;
        vector<pair<int, double>> refuel_plan;
        
        for (int lap = 1; lap <= n; lap++) {
            // 计算这一圈的时间
            double lap_time = t0 + t1 * current_fuel;
            time += lap_time;
            
            // 计算这一圈消耗的油
            double lap_fuel = f0 + f1 * current_fuel;
            current_fuel -= lap_fuel;
            
            // 如果油不够跑下一圈，需要进站
            if (lap < n && current_fuel < f0 + f1 * 0) {
                double need = f - current_fuel;
                time += pit_time + fuel_time * need;
                current_fuel = f;
                stops++;
                refuel_plan.push_back({lap, need});
            }
        }
        
        if (time < min_time) {
            min_time = time;
            best_fuel = f;
            best_stops = stops;
        }
    }
    
    printf("%.3f %.3f %d\n", min_time, best_fuel, best_stops);
    
    return 0;
}
