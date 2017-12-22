#include <cassert>
#include <iostream>
#include <string>
#include <set>

typedef std::pair<int, int> XY;

void draw(const std::set<XY>& infected, const XY& p) {
    int min_x = p.first;
    int max_x = p.first;
    int min_y = p.second;
    int max_y = p.second;
    
    for (auto i: infected) {
        min_x = std::min(min_x, i.first);
        max_x = std::max(max_x, i.first);
        min_y = std::min(min_y, i.second);
        max_y = std::max(max_y, i.second);
    }
    
    for (auto y = min_y; y <= max_y; ++y) {
        for (auto x = min_x; x <= max_x; ++x) {
            XY xy{x, y};
            if (xy == p) {
                std::cout << ((infected.find(xy) != infected.end()) ? "[#]" : "[.]");
            } else {
                std::cout << ((infected.find(xy) != infected.end()) ? " # " : " . ");
            }
        }
        std::cout << std::endl;
    }
}
    
int main() {
    std::set<XY> infected;
    XY p;
    XY d{0, -1}; /* 0 -1 = north; 1 0 = east; 0 1 = south; -1 0 = west */
    
    int y = 0;
    for (std::string line; std::getline(std::cin, line); /**/) {
        int x = 0;
        for (auto c: line) {
            if (c == '#') {
                infected.insert(XY{x, y});
            } else {
                assert(c == '.');
            }
            ++x;
        }
        ++y;
    }
    p.first = (y-1)/2;
    p.second = p.first;
    
    int loops = 10000;
    int infections = 0;
    for (int loop = 0; loop < loops; ++loop) {
        std::cout << loop << " " << p.first << "/" << p.second << " " << d.first << "/" << d.second << std::endl;
    
        //draw(infected, p);
        
        auto it = infected.find(p); 
        if (it == infected.end()) {
            // turn left
            std::cout << "left " << d.first << "/" << d.second << " -> ";
            std::swap(d.first, d.second);
            d.second *= -1;
            std::cout << d.first << "/" << d.second << std::endl;
            
            // infect
            infected.insert(p);
            ++infections;
            std::cout << "infect" << std::endl;
        } else {
            // turn right
            
            std::cout << "right " << d.first << "/" << d.second << " -> ";
            std::swap(d.first, d.second);
            d.first *= -1;
            std::cout << d.first << "/" << d.second << std::endl;
            
            // clean
            infected.erase(it);
            std::cout << "clean" << std::endl;
        }
        // forward
        p.first += d.first;
        p.second += d.second;
    }
    
    std::cout << infections << std::endl;
    
    return 0;
}
