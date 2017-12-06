#include <iostream>
#include <iterator>
#include <set>
#include <vector>

void redistribute(std::vector<int>& banks) {
    const int len = banks.size();
    
    // find bank with maximum number of blocks
    int pos = 0;
    for (int i = 1; i < len; ++i) {
        if (banks[i] > banks[pos]) {
            pos = i;
        }
    }
    
    // redistribute blocks of banks[pos]
    int amount = banks[pos];
    banks[pos] = 0;
    while (amount > 0) {
        pos = (pos + 1) % len;
        ++banks[pos];
        --amount;
    }
}

int main() {
    std::vector<int> banks{std::istream_iterator<int>{std::cin}, {}};

    std::set<std::vector<int>> seen;
    while (seen.insert(banks).second) {
        redistribute(banks);
    }
    
#ifdef PART1
    std::cout << seen.size() << std::endl;
#else
    const std::vector<int> witness = banks;
    for (int cycles = 1; true; ++cycles) {
        redistribute(banks);
        if (banks == witness) {
            std::cout << cycles << std::endl;
            break;
        }
    }
#endif    
    return 0;
}
