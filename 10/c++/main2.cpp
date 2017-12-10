#include <iostream>
#include <array>
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
    
    // create dense-hash
    std::array<unsigned char, 16> dense_hash;
    for (auto block = 0; block < 16; ++block) {
        dense_hash[block] = 0;
        for (auto number = 0; number < 16; ++number) {
            dense_hash[block] ^= sparse_hash[16 * block + number]; 
        }
    }
    
    // print dense-hash
    for (auto c: dense_hash) {
        printf("%.02x", c);
    }
    return 0;
}
