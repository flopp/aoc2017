#include <iostream>
#include <iterator>
#include <vector>


int main() {
    std::vector<int> offsets{std::istream_iterator<int>{std::cin}, {}};

    int pos = 0;
    int jumps = 0;
    while (pos >= 0 && pos < (int)offsets.size()) {
        ++jumps;
#ifdef PART1
        pos += (offsets[pos]++);
#else
        if (offsets[pos] >= 3) {
            pos += (offsets[pos]--);
        } else {
            pos += (offsets[pos]++);
        }
#endif
            
    }
    std::cout << jumps << std::endl;
    return 0;
}
