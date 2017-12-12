#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

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
    UF uf;
    int id1, id2;
    for (std::string line; std::getline(std::cin, line); /**/) {
        std::istringstream iss(line);
        iss >> id1; uf.set(id1);
        std::string dummy; iss >> dummy;
        while (iss >> id2) {
            uf.set(id2);
            uf.unite(id1, id2);
            if (iss.peek() == ',') {
                iss.ignore();
            }
        }
    }
    
    std::cout << "group(0) = " << uf.count(0) << std::endl;
    std::cout << "groups = " << uf.groups() << std::endl;
    return 0;
}
