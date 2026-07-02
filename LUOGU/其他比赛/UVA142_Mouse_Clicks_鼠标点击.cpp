// UVA142 - Mouse Clicks (鼠标点击)
// 在500x500屏幕上确定鼠标点击了哪个区域
#include <iostream>
#include <vector>
#include <string>

struct Region {
    int x1, y1, x2, y2; // 左上角和右下角坐标
    char label[10];       // 区域标签
};

int main() {
    std::vector<Region> regions;
    char type;
    
    // 读取区域定义
    while (std::cin >> type && type != 'E') {
        if (type == 'R') {
            Region r;
            std::cin >> r.x1 >> r.y1 >> r.x2 >> r.y2;
            // 确保 x1 <= x2, y1 <= y2
            if (r.x1 > r.x2) std::swap(r.x1, r.x2);
            if (r.y1 > r.y2) std::swap(r.y1, r.y2);
            // 读取标签
            std::cin.ignore(); // 忽略空格
            std::cin.getline(r.label, 10);
            regions.push_back(r);
        }
    }
    
    // 读取鼠标点击
    int mx, my;
    while (std::cin >> mx >> my && (mx != -1 || my != -1)) {
        bool found = false;
        
        // 从后往前检查（后定义的区域优先）
        for (int i = regions.size() - 1; i >= 0; i--) {
            const Region& r = regions[i];
            
            // 检查点击是否在区域内（包括边界）
            if (mx >= r.x1 && mx <= r.x2 && my >= r.y1 && my <= r.y2) {
                std::cout << r.label << std::endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            std::cout << "Miss" << std::endl;
        }
    }
    
    return 0;
}
