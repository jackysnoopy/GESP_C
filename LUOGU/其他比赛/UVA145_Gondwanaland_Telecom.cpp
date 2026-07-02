#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

const double rates[3][3] = {
    {0.10, 0.06, 0.02},  // Gondwanaland
    {0.25, 0.15, 0.05},  // Centreville
    {0.53, 0.33, 0.13}   // Snowfall
};

int timeToMinutes(const string& time) {
    int h = stoi(time.substr(0, 2));
    int m = stoi(time.substr(3, 2));
    return h * 60 + m;
}

int getTimePeriod(int minutes) {
    int hour = minutes / 60;
    if (hour >= 8 && hour < 18) return 0;
    if (hour >= 18 && hour < 22) return 1;
    return 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string city_code, start_time, end_time;
    while (cin >> city_code >> start_time >> end_time && city_code != "#") {
        int start_minutes = timeToMinutes(start_time);
        int end_minutes = timeToMinutes(end_time);
        
        if (end_minutes <= start_minutes) {
            end_minutes += 24 * 60;
        }
        
        int city_index = 0;
        if (city_code == "C") city_index = 1;
        else if (city_code == "S") city_index = 2;
        
        int total_minutes = 0;
        double total_cost = 0.0;
        
        for (int t = start_minutes; t < end_minutes; ++t) {
            int period = getTimePeriod(t % (24 * 60));
            total_cost += rates[city_index][period];
            ++total_minutes;
        }
        
        cout << setw(3) << city_code << " " 
             << setw(8) << start_time << " " 
             << setw(8) << end_time << " " 
             << setw(6) << total_minutes << " " 
             << fixed << setprecision(2) << total_cost << endl;
    }
    
    return 0;
}
