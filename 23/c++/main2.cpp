#include <iostream>

bool is_prime(const int64_t& b) {
    for (int64_t d = 2; d < b; ++d) {
        if ((b % d) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int64_t non_primes = 0;
    for (int64_t bb = 0; bb < 1001; ++bb) {
        if (!is_prime(106700 + 17 * bb)) {
            ++non_primes;
        }
    }
    std::cout << non_primes << std::endl;
    return 0;
}
