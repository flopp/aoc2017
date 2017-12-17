#include <iostream>
#include <string>
#include <vector>
#include <time.h>

int main(int /*argc*/, char* argv[]) {
    const int steps = std::stoi(argv[1]);
    
#ifdef PART1
    const int insertions = 2017;
#else
    const int insertions = 50000000;
#endif
    std::vector<std::pair<int, int>> pos(insertions + 1);
    for (int i = 0; i <= insertions; ++i) {
        pos[i].first = i;
        pos[i].second = 0;
    }
    int p = 0;
    
    double last_t = clock() / (double)CLOCKS_PER_SEC;
    for (int i = 1; i <= insertions; ++i) {
        if ((i % 1000000) == 0) {
            double t = clock() / (double)CLOCKS_PER_SEC;
            std::cout << (i / 1000000) << " " << (t - last_t) << std::endl;
            last_t = t;
        }
        for (int step = 0; step < steps; ++step) {
            p = pos[p].second;
        }
        pos[i].second = pos[p].second;
        pos[p].second = i;
        p = i;
    }

#ifdef PART2
    while (pos[p].first != 0) {
        p = pos[p].second;
    }
#endif
    std::cout << pos[pos[p].second].first << std::endl;

    return 0;
}
