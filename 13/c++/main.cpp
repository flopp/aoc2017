#include <iostream>
#include <utility>
#include <vector>

#ifdef PART1
int main() {
    int severity = 0;
    for (int depth, range; std::cin >> depth, std::cin.ignore(), std::cin >> range; /**/) {
        if ((depth % (2 * range - 2)) == 0) {
            severity += depth * range;
        }
    }
    std::cout << severity << std::endl;
    return 0;
}
#else
int main() {
    std::vector<std::pair<int, int>> scanners;
    for (int depth, range; std::cin >> depth, std::cin.ignore(), std::cin >> range; /**/) {
        scanners.push_back({depth, 2 * range - 2});
    }
    
    for (int delay = 0; /**/; ++delay) {
        bool detected = false;
        for (const auto& s: scanners) {
            if (((delay + s.first) % s.second) == 0) {
                detected = true;
                break;
            }
        }
        if (!detected) {
            std::cout << delay << std::endl;
            break;
        }
    }
    return 0;
}
#endif