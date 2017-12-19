#include <iostream>
#include <string>
#include <vector>

struct XY {
    int x, y;
    
    bool operator==(const XY& other) const {
        return (x == other.x) && (y == other.y);
    }
    
    XY& operator+=(const XY& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    XY operator+(const XY& other) const{
        XY res{*this};
        return res += other;
    }
};

int main() {
    std::vector<std::string> pipes;
    for (std::string line; std::getline(std::cin, line); /**/) {
        pipes.push_back(line);
    }
    const int w = pipes[0].size();
    const int h = pipes.size();
    
    XY pos{0, 0};
    while (pipes[pos.y][pos.x] != '|') {
        ++pos.x;
    }
    XY dir{0, 1};
    
    int steps = 1;
    std::string path;
    for (;;) {
        pos += dir;        
        const char& c = pipes[pos.y][pos.x];
        if (c == ' ') {
            break;
        } else if ((c == '|') || (c == '-')) {
            ++steps;
            /**/
        } else if (('A' <= c) && (c <= 'Z')) {
            ++steps;
            path += c;
        } else if (c == '+') {
            ++steps;
            XY d{dir.y, dir.x};
                        
            auto p = pos + d;
            if ((p.x >= 0) && (p.x < w) && (p.y >= 0) && (p.y < h) &&
                (pipes[p.y][p.x] != ' ')) {
                dir = d;
                continue;
            }
            
            d.x *= -1;
            d.y *= -1;
            p = pos + d;
            if ((p.x >= 0) && (p.x < w) && (p.y >= 0) && (p.y < h) &&
                (pipes[p.y][p.x] != ' ')) {
                dir = d;
                continue;
            }
            
            break;
        }
    }
    
    std::cout << path << " " << steps << std::endl;
    
    return 0;
}
