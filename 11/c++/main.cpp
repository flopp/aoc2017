#include <iostream>
#include <sstream>
#include <string>

/*

  \ n  /
nw +--+ ne
  /    \
-+      +-
  \    /
sw +--+ se
  / s  \

*/

int dist(int x, int y) {
    auto z = y - (x + (x & 1)) / 2;
    return std::max(std::abs(x), std::max(std::abs(x + z), std::abs(z)));
}

int main() {
    for (std::string line; std::getline(std::cin, line); /**/) {
        auto x = 0;
        auto y = 0;
        auto m = 0;
        auto iss = std::istringstream(line);
        for (std::string dir; std::getline(iss, dir, ',' ); /**/) {
            if (dir == "n") {
                --y;
            } else if (dir == "s") {
                ++y;
            } else if (dir == "nw") {
                if (x & 1) {
                    --y;
                }
                --x;
            } else if (dir == "ne") {
                if (x & 1) {
                    --y;
                }
                ++x;
            } else if (dir == "sw") {
                if (!(x & 1)) {
                    ++y;
                }
                --x;
            } else if (dir == "se") {
                if (!(x & 1)) {
                    ++y;
                }
                ++x;
            }
            
            m = std::max(m, dist(x, y));
        }
        
        std::cout << x << "/" << y << " -> dist=" << dist(x, y) << " max=" << m << std::endl;
    }
    return 0;
}
