#include <iostream>
#include <string>

template <uint64_t factor, uint64_t mask = 0ull>
struct Generator {
    uint64_t state;

    void next() {
        do {
            state *= factor;
            state %= 2147483647ull;
        } while ((state & mask));
    }
};


int main() {    
#ifdef PART1
    const int rounds = 40000000;
    Generator<16807> A;
    Generator<48271> B;
#else
    const int rounds = 5000000;
    Generator<16807, 0x3> A;
    Generator<48271, 0x7> B;
#endif

    std::string line;

    std::getline(std::cin, line);
    A.state = stoi(line.substr(24));
    
    std::getline(std::cin, line);
    B.state = stoi(line.substr(24));
    
    int equal_pairs = 0;
    for (int i = 0; i < rounds; ++i) {
        A.next();
        B.next();
        if ((A.state & 0xFFFFu) == (B.state & 0xFFFFu)) {
            ++equal_pairs;
        }
    }
    
    std::cout << equal_pairs << std::endl;
    
    return 0;
}
