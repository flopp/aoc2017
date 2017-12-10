#include <array>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    // initialize sparse-hash
    auto sparse_hash = std::array<unsigned char, 256>{};
    for (int i = 0; i < 256; ++i) {
        sparse_hash[i] = i;
    }
    
    // read in lengths, append static 'initialization vector'
    std::vector<unsigned char> lengths;
    for (char c; std::cin.get(c); /**/) {
        lengths.push_back((unsigned char)c);
    }
    for (auto c: {17, 31, 73, 47, 23}) {
        lengths.push_back((unsigned char)c);
    }
    
    // apply 64 rounds of rotations
    auto pos = 0;
    auto skip = 0;
    for (int round = 0; round < 64; ++round) {
        for (auto length: lengths) {
            auto p1 = pos;
            auto p2 = pos + length - 1;
            for (/**/; p1 < p2; ++p1, --p2) {
                std::swap(sparse_hash[p1 & 0xFF], sparse_hash[p2 & 0xFF]);
            }
            pos = (pos + length + (skip++)) & 0xFF;
        }
    }
    
    // create & print dense-hash
    for (auto block = sparse_hash.begin(); block != sparse_hash.end(); std::advance(block, 16)) {
        printf("%02x", std::accumulate(block, block + 16, (unsigned char)0, std::bit_xor<unsigned char>()));
    }
    
    return 0;
}
