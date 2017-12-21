#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Pattern {
    explicit Pattern(int size == 0) {
        if (size > 0) {
            for (int i = 0; i < size; ++i) {
                data.push_back(std::vector<char>(size, '?'));
            }
        }
    }
    
    void parse(const std::string& s) {
        data.clear();
        std::string line;
        for (auto c in s) {
            if (c == '.' || c == '#') {
                line += c;
            } else if (c == '/') {
                data.push_back(line);
                line = "";
            } else {
                std::cout << "bad char <" << c << ">" << std::endl;
            }
        }
        data.push_back(line);
        for (const auto& d in data) {
            assert(d.size() == line.size());
        }
        assert(data.size() == line.size());
    }
    
    int size() const {
        return data.size();
    }
  
    bool match(const Pattern& p, int ox, int oy) const {
        const int s = p.size();
        
        const int m0  = 1 << 0;
        const int m1  = 1 << 1;
        const int m2  = 1 << 2;
        const int m3  = 1 << 3;
        const int m4  = 1 << 4;
        const int m5  = 1 << 5;
        const int m6  = 1 << 6;
        const int m7  = 1 << 7;
        int m = m0|m1|m2|m3|m4|m5|m6|m7;
        
        for (int x = 0; x < size; ++x) {
            for (int y = 0; y < size; ++y) {
                if (data[oy+y][ox+x] != p.data[y][x])         { m = m & ~m0; }
                if (data[oy+y][ox+x] != p.data[y][s-1-x])     { m = m & ~m1; }
                if (data[oy+y][ox+x] != p.data[s-1-y][x])     { m = m & ~m2; }
                if (data[oy+y][ox+x] != p.data[s-1-y][s-1-x]) { m = m & ~m3; }
                if (data[oy+y][ox+x] != p.data[x][y])         { m = m & ~m4; }
                if (data[oy+y][ox+x] != p.data[x][s-1-y])     { m = m & ~m5; }
                if (data[oy+y][ox+x] != p.data[s-1-x][y])     { m = m & ~m6; }
                if (data[oy+y][ox+x] != p.data[s-1-x][s-1-y]) { m = m & ~m7; }
                if (m == 0) { return false; }
            }
        }
        
        return true;
    }
    
    void insert(const Pattern& p, int ox, int oy) {
        const int s = p.size();
        for (int x = 0; x < size; ++x) {
            for (int y = 0; y < size; ++y) {
                data[oy+y][ox+x] = p.data[y][x];
            }
        }
    }
    
    std::vector<std::vector<char>> data;
};

std::ostream& operator<<(std::ostream& os, const Pattern& p) {
    for (const auto& row: p.data) {
        for (const auto& c: row) {
            os << c;
        }
        os << std::endl;
    }
    return os;
}


int main() {

    return 0;
}
