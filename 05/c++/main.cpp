#include <iostream>
#include <vector>


int main() {
    std::vector<int> offsets;
    for (int i; std::cin >> i; /**/) {
        offsets.push_back(i);
    }

    int pos = 0;
    int jumps = 0;
    while (pos >= 0 && pos < (int)offsets.size()) {
        ++jumps;
#ifdef PART1
        pos += (offsets[pos]++);
#else
        const int oldpos = pos;
        pos += offsets[pos];
        offsets[oldpos] += (offsets[oldpos] >= 3) ? -1 : +1;
#endif
            
    }
    std::cout << jumps << std::endl;
    return 0;
}
