#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Pattern {
    explicit Pattern(int size = 0) {
        if (size > 0) {
            std::string s;
            s.assign(size, '?');
            for (int i = 0; i < size; ++i) {
                data.push_back(s);
            }
        }
    }
    
    void parse(const std::string& s) {
        data.clear();
        std::string line;
        for (auto c: s) {
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
        for (const auto& d: data) {
            assert(d.size() == line.size());
        }
        assert(data.size() == line.size());
    }
    
    int size() const {
        return data.size();
    }
    
    int on() const {
        int count{0};
        for (const auto& s: data) {
            for (const auto& c: s) {
                if (c == '#') {
                    ++count;
                }
            }
        }
        return count;
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
        
        for (int x = 0; x < s; ++x) {
            for (int y = 0; y < s; ++y) {
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
        for (int x = 0; x < s; ++x) {
            for (int y = 0; y < s; ++y) {
                data[oy+y][ox+x] = p.data[y][x];
            }
        }
    }
    
    std::vector<std::string> data;
};

typedef std::pair<Pattern, Pattern> Rule;

int main() {
    std::vector<Rule> rules2, rules3;
    for (std::string pattern, dummy, result; std::cin >> pattern >> dummy >> result; /**/) {
        Rule r;
        r.first.parse(pattern);
        r.second.parse(result);
        if (r.first.size() == 2) {
            rules2.push_back(r);
            assert(r.second.size() == 3);
        } else if (r.first.size() == 3) {
            rules3.push_back(r);
            assert(r.second.size() == 4);
        } else {
            assert(false);
        }
    }
    
    Pattern grid;
    grid.parse(".#./..#/###");
    
#ifdef PART1
#ifdef TEST
    const int loops = 2;
#else
    const int loops = 5;
#endif
#else
    const int loops = 18;
#endif
    for (int loop = 0; loop < loops; ++loop) {
        if ((grid.size() % 2) == 0) {
            const int s = grid.size() / 2;
            Pattern grid2(s * 3);
            for (int x = 0; x < s; ++x) {
                for (int y = 0; y < s; ++y) {
                    for (const auto& r: rules2) {
                        if (grid.match(r.first, x*2, y*2)) {
                            grid2.insert(r.second, x*3, y*3);
                            break;
                        }
                    }
                }
            }
            grid = grid2;
        } else {
            assert((grid.size() % 3) == 0);
            const int s = grid.size() / 3;
            Pattern grid2(s * 4);
            for (int x = 0; x < s; ++x) {
                for (int y = 0; y < s; ++y) {
                    for (const auto& r: rules3) {
                        if (grid.match(r.first, x*3, y*3)) {
                            grid2.insert(r.second, x*4, y*4);
                            break;
                        }
                    }
                }
            }
            grid = grid2;
        }
    }
    
    std::cout << grid.on() << std::endl;
    
    return 0;
}
