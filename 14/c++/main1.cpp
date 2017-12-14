#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>


std::array<unsigned char, 16> knot_hash(const std::vector<unsigned char>& data) {
    // initialize sparse-hash
    auto sparse_hash = std::array<unsigned char, 256>{};
    for (int i = 0; i < 256; ++i) {
        sparse_hash[i] = i;
    }
    
    // apply 64 rounds of rotations
    auto pos  = int{0};
    auto skip = int{0};
    for (int round = 0; round < 64; ++round) {
        for (auto length: data) {
            auto p1 = pos;
            auto p2 = pos + length - 1;
            for (/**/; p1 < p2; ++p1, --p2) {
                std::swap(sparse_hash[p1 & 0xFF], sparse_hash[p2 & 0xFF]);
            }
            pos = (pos + length + (skip++)) & 0xFF;
        }
        for (auto length: {17, 31, 73, 47, 23}) {
            auto p1 = pos;
            auto p2 = pos + length - 1;
            for (/**/; p1 < p2; ++p1, --p2) {
                std::swap(sparse_hash[p1 & 0xFF], sparse_hash[p2 & 0xFF]);
            }
            pos = (pos + length + (skip++)) & 0xFF;
        }
    }
    
    // create & print dense-hash
    std::array<unsigned char, 16> dense_hash;
    auto d = dense_hash.begin();
    for (auto block = sparse_hash.begin(); block != sparse_hash.end(); std::advance(block, 16), ++d) {
        *d = std::accumulate(block, block + 16, (unsigned char)0, std::bit_xor<unsigned char>());
    }
    return dense_hash;
}


struct UF {
    void set(int i) {
        if (mapping.insert({i, sets.size()}).second) {
            sets.push_back(sets.size());
        }
    }
    
    void unite(int i, int j) {
        auto ii = sets[mapping[i]];
        auto jj = sets[mapping[j]];
        if (ii != jj) {
            for (auto it = sets.begin(); it != sets.end(); ++it) {
                if (*it == jj) {
                    *it = ii;
                }
            }
        }
    }
    
    std::size_t count(int i) {
        auto ii = sets[mapping[i]];
        std::size_t c = 0;
        for (const auto& s: sets) {
            if (s == ii) {
                ++c;
            }
        }
        return c;
    }

    std::size_t groups() {
        std::set<std::size_t> g;
        for (const auto& s: sets) {
            g.insert(s);
        }
        return g.size();
    }
    std::map<int, std::size_t> mapping;
    std::vector<std::size_t> sets;
};


int main() {
    std::string base;
    std::cin >> base;
    
    int next = 1;
    std::vector<int> grid;
    UF uf;
    
    int set_bits = 0;
    for (int row = 0; row < 128; ++row) {
        std::ostringstream oss;
        oss << base << "-" << row;
        std::vector<unsigned char> data;
        for (auto c: oss.str()) {
            data.push_back((unsigned char)c);
        }
        
        int col = 0;
        for (auto c: knot_hash(data)) {
            for (auto mask = 0x80; mask != 0x00; mask >>= 1) {
                if (c & mask) {
                    std::cout << "#";
                    ++set_bits;

                    uf.set(next);
                    grid.push_back(next);

                    if ((col > 0) && (grid[col - 1 + row * 128] != 0)) {
                        uf.unite(next, grid[col - 1 + row * 128]);
                    }
                    if ((row > 0) && (grid[col + row * 128 - 128] != 0)) {
                        uf.unite(next, grid[col + row * 128 - 128]);
                    }

                    ++next;
                } else {
                    std::cout << ".";
                    grid.push_back(0);
                }
                ++col;
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "set bits: " << set_bits << std::endl;
    std::cout << "regions: " << uf.groups() << std::endl;
    
    return 0;
}
